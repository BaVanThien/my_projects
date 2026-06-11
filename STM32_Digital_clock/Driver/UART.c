#include "UART.h"         // own header ¡ª already present
#include "String.h"       // character_to_number ¡ª already present
#include "main.h"         // RingBuffer, DmaBuffer, g_IsTimeSynced...
#include "DS3231.h"       // DS3231_Set_Time, DS3231_Set_Day
#include "RCC.h"          // RCC_Enable_PortA, RCC_Enable_AFIO, RCC_Enable_UART1
#include "GPIO.h"         // GPIO_Config
#include "Tim.h"          // time_c/time_n
#include "DMA.h"        // DMA_CNDTR5, DMA_BUF_SIZE

//#define BUFFER_SIZE 30
//uint8_t RxBuffer[BUFFER_SIZE];        // arr store data
static volatile uint8_t index_In = 0;    // index write data
static volatile uint8_t index_Out = 0;
static volatile uint8_t Rx_Byte_read;
static volatile uint8_t index_cmdBuff = 0;

//volatile uint8_t DmaBuffer[DMA_BUF_SIZE];
//volatile uint8_t RingBuffer[RING_BUF_SIZE];
static  uint16_t last_dma_pos = 0;

#define BAUD_RATE 9600
#define SYS_CLOCK 8000000
#define MANTISSA (SYS_CLOCK / (16 * BAUD_RATE))
#define FRACTION (((SYS_CLOCK % (16 * BAUD_RATE)) * 16) / (16 * BAUD_RATE))

void UART1_Init(void)
{
    // Enable clock port A;
    RCC_Enable_PortA();
    RCC_Enable_AFIO();
    RCC_Enable_UART1();
    //PA9:output  AF PP_TX
    GPIO_Config(GPIOA,GPIO_PIN_9,GPIO_MODE_AF_PP);
    //PA10: input  AF FLOATING_RX
    GPIO_Config(GPIOA,GPIO_PIN_10,GPIO_MODE_INPUT_FLOATING);
    USART1_BRR = (MANTISSA << 4) | (FRACTION & 0x0F);   //set baudrate 9600 bps.
    USART1_CR1 |= (1<<13);                              //UE: USART Enable
    USART1_CR1 |= (1<<3);                               //TE: transmitter enable
    USART1_CR1 |= (1<<2);                               //RE: TRansmitter is enable
    USART1_CR3 |= (1 << 6);                             //(Bit DMAR - DMA Enable Receiver).
//	USART1_CR1 |= (1<<5);                               //RXNE interrupt enable

}
void UART1_SendChar(char c)
{
    while(!(USART1_SR &(1 << 7)));// TXE
    USART1_DR = c;
}
void UART1_SendString(const char *str)
{
    while(*str)
    {
        UART1_SendChar(*str++);
    }
}

void CheckRxBuffer( uint8_t *str_Ring, uint8_t *str_Cmd,uint16_t ring_size)
{
    while (index_Out != index_In)
    {
        Rx_Byte_read = str_Ring[index_Out];

        if (Rx_Byte_read == '[')
        {
            index_cmdBuff = 0;                          /* Reset index cmd Buffer  */
        }

        str_Cmd[index_cmdBuff] = Rx_Byte_read;

        if (index_cmdBuff < BUFFER_SIZE - 1)
        {
            index_cmdBuff++;                               /* encre index cmd Buffer */
        }

        if (Rx_Byte_read == ']')
        {
            str_Cmd[index_cmdBuff] = 0;                      //Add a string termination character.

            if (str_Cmd[0] == '[')                            /*Make sure it has the opening character. */
            {
                process_CmdBuffer(str_Cmd);                  // Call the handler function and pass the global array
            }

            str_Cmd[0] = 0;                                  /* Reset character */
        }

        index_Out++;
        if (index_Out >= ring_size) index_Out = 0;
    }
}

void process_CmdBuffer(uint8_t *p_cmdBuffer)
{
    // --- STEP 1: CHECK FORMATTING (Collision Marks: : and /) ---;
    // Standard format: [HH:MM:SS DD/MM/YY] -> positions 3, 6, 9, 12, and 15 must be correct
    if (p_cmdBuffer[3]  != ':' || p_cmdBuffer[6]  != ':' ||
            p_cmdBuffer[9]  != ' ' ||
            p_cmdBuffer[12] != '/' || p_cmdBuffer[15] != '/'||
            p_cmdBuffer[18] != ']')
    {
     // Send a warning to the UART and exit immediately; do not proceed further.
        UART1_SendString("Error: Wrong Format! Please use [HH:MM:SS DD/MM/YY]\r\n");
        return;
    }

    // --- STEP 2: EXTRACT DATA FROM THE p_cmdBuffer CURSOR ---
    /* get hour from p_cmdBuffer */
    time_c.hour[0] = p_cmdBuffer[1];
    time_c.hour[1] = p_cmdBuffer[2];
    time_n.hour = (uint8_t)character_to_number(time_c.hour, 2);

    /* get minute from p_cmdBuffer */
    time_c.minute[0] = p_cmdBuffer[4];
    time_c.minute[1] = p_cmdBuffer[5];
    time_n.minute = (uint8_t)character_to_number(time_c.minute, 2);

    /* get second from p_cmdBuffer */
    time_c.second[0] = p_cmdBuffer[7];
    time_c.second[1] = p_cmdBuffer[8];
    time_n.second = (uint8_t)character_to_number(time_c.second, 2);

    /* get day from p_cmdBuffer */
    date_c.day[0] = p_cmdBuffer[10];
    date_c.day[1] = p_cmdBuffer[11];
    date_n.day = (uint8_t)character_to_number(date_c.day, 2);

    /* get month from p_cmdBuffer */
    date_c.month[0] = p_cmdBuffer[13];
    date_c.month[1] = p_cmdBuffer[14];
    date_n.month = (uint8_t)character_to_number(date_c.month, 2);

    /* get year from p_cmdBuffer */
    date_c.year[0] = p_cmdBuffer[16];
    date_c.year[1] = p_cmdBuffer[17];
    date_n.year = (uint8_t)character_to_number(date_c.year, 2);

    // ---  CHECK STANDRT TIME ---
    if (time_n.hour >= 24 || time_n.minute >= 60 || time_n.second >= 60 ||
            date_n.day < 1   || date_n.day > 31    ||
            date_n.month < 1 || date_n.month > 12)
    {
    // --- STEP 3: CHECK THE LOGICAL CONDITIONS OF THE NUMBER (Time Validity) ---
        UART1_SendString("Error: Invalid Time or Date value!\r\n");
        return;
    }
    // SET RTC and update time
    DS3231_Set_Time(time_n.hour, time_n.minute, time_n.second);
    DS3231_Set_Day(date_n.day, date_n.month, date_n.year);

    // --- STEP 3: CHECK THE LOGICAL CONDITIONS OF THE NUMBER (Time Validity) ---

    if (g_IsTimeSynced == 0)
    {
        g_IsTimeSynced = 1;
        g_ScreenChangedFlag = 1;
    }

    UART1_SendString("Update RTC Success!\r\n");
}

void Update_RingBuffer_From_DMA(uint8_t *str_Ring,uint8_t *str_dma)
{
    uint16_t current_dma_pos = DMA_BUF_SIZE - (uint16_t)DMA_CNDTR5;

    while (last_dma_pos != current_dma_pos)
    {
        // coppy  buffer DMA v¨¤o Ring Buffer
        str_Ring[index_In] = str_dma[last_dma_pos];
        index_In++;
        if (index_In >= RING_BUF_SIZE) index_In = 0;

        last_dma_pos++;
        if (last_dma_pos >= DMA_BUF_SIZE) last_dma_pos = 0;
    }
}


