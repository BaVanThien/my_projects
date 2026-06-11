
#include "UART_task.h"    // own header
#include "main.h"         // RingBuffer, DmaBuffer, RING_BUF_SIZE
#include "UART.h"         // Update_RingBuffer_From_DMA, CheckRxBuffer

void UART_Task(void)
{
    Update_RingBuffer_From_DMA(RingBuffer,DmaBuffer);
    CheckRxBuffer(RingBuffer,RxBuffer,RING_BUF_SIZE);
}
