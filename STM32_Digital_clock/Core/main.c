#include "main.h"         // extern vars, enum, defines
#include "RCC.h"          // System_Clock_Init g?i RCC_Enable_*
#include "GPIO.h"         // GPIO_Config PA0, PA1
#include "EXTI.h"         // EXIT0_Init, EXTI1_Init
#include "Tim.h"          // TIM2_init_IT, TIM3_init_IT
#include "UART.h"         // UART1_Init, UART1_SendString
#include "DMA.h"          // DAM1_UART_Init
#include "I2C.h"          // I2C_Init
#include "SPI.h"          // SPI1_Init_Master
#include "TFT.h"          // initTFT, fullDisplay, Update_Clock_Display
#include "BUTTON.h"       // Button_Task (khai b¨¢o trong BUTTON.h)
#include "UART_task.h"    // UART_Task
#include "Display_task.h" // Display_Task, Update_Clock_Display
/* ========================================================================== */
/*  GLOBAL VARIABLES
 ========================================================================== */

// --------------------------------------------------------------------------
//SYSTEM STATE MANAGEMENT & SCREEN NAVIGATION (STATE MACHINE)
// --------------------------------------------------------------------------
volatile DisplayMode_t g_DisplayMode = DISPLAY_MODE_TIME;     // BUTTON
volatile DisplayStatus_t g_DisplayStatus = DISPLAY_STATUS_ON; // BUTTON
volatile uint8_t g_ScreenChangedFlag = 0;                     
volatile uint8_t g_DisplayModeToggleFlag = 0;
volatile uint8_t g_UpdateDisplayFlag = 0;// TIM3
// --------------------------------------------------------------------------
// BUTTON FLAGS EVENT
// --------------------------------------------------------------------------
volatile uint8_t g_Button1PressedFlag = 0;
volatile uint8_t g_Button2PressedFlag = 0;

// --------------------------------------------------------------------------
// REAL-TIME DATA (RTC DS3231 DATA)
// --------------------------------------------------------------------------
volatile uint8_t g_IsTimeSynced = 0;
volatile uint8_t rtc_h, rtc_m, rtc_s;
volatile uint8_t rtc_d, rtc_mt, rtc_y;

// --------------------------------------------------------------------------
// UART DATA TRANSMISSION & DMA BUFFERS
// --------------------------------------------------------------------------
uint8_t RxBuffer[BUFFER_SIZE];
uint8_t DmaBuffer[DMA_BUF_SIZE];
uint8_t RingBuffer[RING_BUF_SIZE];

/* ========================================================================== */

void System_Clock_Init(void)
{
    RCC_Enable_DMA1();
    RCC_Enable_PortA();
    RCC_Enable_PortB();
    RCC_Enable_AFIO();
    RCC_Enable_UART1();
    RCC_Enable_TIM2();
    RCC_Enable_TIM3();
    RCC_Enable_I2C1();
    RCC_Enable_SPI1();
}
int main()
{
    System_Clock_Init();

    TIM2_init_IT();
    TIM3_init_IT();
    EXIT0_Init();
    EXTI1_Init();
    UART1_Init();
    DAM1_UART_Init(DmaBuffer, DMA_BUF_SIZE);
    I2C_Init();
    SPI1_Init_Master();
    initTFT();

    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT_PD);
    GPIO_Config(GPIOA, GPIO_PIN_1, GPIO_MODE_INPUT_PD);

    UART1_SendString("=== System Started ===\r\n");    //check  
    fullDisplay(0x1098);
    Update_Clock_Display();
    while (1)
    {
        Button_Task();
        UART_Task();
        Display_Task();
    }
}
