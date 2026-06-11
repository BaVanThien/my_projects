#include "DMA.h"          // own header ¡ª already present
#include "UART.h"         // USART1_DR (register address)



void DAM1_UART_Init(uint8_t * buffer, uint16_t size)
{
    // config address and size
    DMA_CCR5 &= ~(uint32_t)(1 << 0);   //off DMA

    DMA_CPAR5 = (uint32_t)&USART1_DR;  //  assign address USART1 Data Register
    DMA_CMAR5 = (uint32_t)buffer;       // assign address
    DMA_CNDTR5 = size;

    DMA_CCR5 |= (1 << 7) | (1 << 5) | (1 << 1) | (1 << 0);
    DMA_CCR5 &=~(uint32_t)(1 << 1);

}

void DMA1_Reset(uint16_t size)
{
    DMA_CCR5 &= ~(uint32_t)(1 << 0);
    DMA_CNDTR5 = size;
    DMA_CCR5 |= (1 << 0);              // on DAM again
}

