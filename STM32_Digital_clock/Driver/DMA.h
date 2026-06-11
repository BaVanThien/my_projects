#ifndef __DMA_H
#define __DMA_H
#include <stdint.h>
/*-----------ADD_BASE------------------------*/

#define DMA1_BASE        0x40020000UL
/*-----------ADD_offet--------*/
#define DMA_CCR5_ADDR       (DMA1_BASE + 0x058)
#define DMA_CNDTR5_ADDR     (DMA1_BASE + 0x05C)
#define DMA_CPAR5_ADDR      (DMA1_BASE + 0x060)
#define DMA_CMAR5_ADDR      (DMA1_BASE + 0x064)
#define DMA1_ISR_ADDR       (DMA1_BASE + 0x000)
#define DMA1_IFCR_ADDR       (DMA1_BASE +0x004)
/*-----------------DMACR5--------------------*/

#define DMA_CCR5            (*(volatile uint32_t*)(DMA_CCR5_ADDR))
#define DMA_CNDTR5          (*(volatile uint32_t*)(DMA_CNDTR5_ADDR))
#define DMA_CPAR5           (*(volatile uint32_t*)(DMA_CPAR5_ADDR))
#define DMA_CMAR5           (*(volatile uint32_t*)(DMA_CMAR5_ADDR))
#define DMA1_ISR          	(*(volatile uint32_t*)(DMA1_ISR_ADDR))
#define DMA1_IFCR           (*(volatile uint32_t*)(DMA1_IFCR_ADDR))


void DAM1_UART_Init(uint8_t * buffer, uint16_t size);
void DMA1_Reset(uint16_t size);


#endif
