#ifndef __UART_H
#define __UART_H
#include<stdint.h>
#include"GPIO.h"


/*------------ADD_BASE_UART--------*/
#define UART_ADD_BASE   0x40013800UL   

/*------------ADD_OFFSET_UART--------*/
#define USART_SR_OFFSET         0x00
#define USART_DR_OFFSET         0x04
#define USART_BRR_OFFSET        0x08
#define USART_CR1_OFFSET        0x0c
#define USART_CR2_OFFSET        0x10
#define USART_CR3_OFFSET        0x14
#define USART_GTPR_OFFSET       0x18
/*------------UART01--------------*/

#define USART1_SR         (*(volatile uint32_t*)(UART_ADD_BASE  + USART_SR_OFFSET  ))
#define USART1_DR         (*(volatile uint32_t*)(UART_ADD_BASE  + USART_DR_OFFSET  ))
#define USART1_BRR        (*(volatile uint32_t*)(UART_ADD_BASE  + USART_BRR_OFFSET ))
#define USART1_CR1        (*(volatile uint32_t*)(UART_ADD_BASE  + USART_CR1_OFFSET ))
#define USART1_CR2        (*(volatile uint32_t*)(UART_ADD_BASE  + USART_CR2_OFFSET ))
#define USART1_CR3        (*(volatile uint32_t*)(UART_ADD_BASE  + USART_CR3_OFFSET ))
#define USART1_GTP        (*(volatile uint32_t*)(UART_ADD_BASE  + USART_GTPR_OFFSET))
/*------------------------API--------------*/
void UART1_Init(void);
void UART1_SendChar(char c);
void UART1_SendString(const char *str);
void USART1_IRQHandler(void);
void process_CmdBuffer(uint8_t *p_cmdBuffer);  
void DMA1_Channel5_IRQHandler(void);

void Update_RingBuffer_From_DMA(uint8_t *str_Ring,uint8_t *str_dma);
uint16_t number_to_character(uint16_t value, uint8_t data[], uint8_t index);
void CheckRxBuffer( uint8_t *str_Ring, uint8_t *str_Cmd,uint16_t ring_size);

#endif


