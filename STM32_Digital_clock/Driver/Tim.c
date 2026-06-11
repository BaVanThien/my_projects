#include "Tim.h"          // own header ¡ª already present
#include "main.h"         // g_UpdateDisplayFlag (used in TIM3_IRQHandler)
#include "EXTI.h"         // NVIC_ISER0

// Fsty = 8000mhz
//        Fsty      8000
//  f =  ------- =  ------- = 1mhz = 1000 stick each secon, 1ms 1 styck
//       PSC + 1    8000
//        1
//   t = ----
//        f

volatile uint8_t blink_status = 0;

void TIM2_init_IT(void)
{
    TIM2_PSC = 7999;                    //39999; //7999;//TIMx prescale//1000 step each seccon/ 1 ms is step
    TIM2_ARR = 999;                     // Auto-Reload Register/
    TIM2_CNT = 0;
    TIM2_SR  &= ~(uint32_t)(1 << 0);   // clea flat
    TIM2_DIER |= (1 << 0);             // Trigger interrupt enable,Interrupt enable register
    TIM2_CR1  |= (1 << 0);             // TIMx control register 1 CEN: Conter enable
    NVIC_ISER0 |= (1 << 28);
}

void TIM2_IRQHandler(void)
{
    if(TIM2_SR & 0x01)                 //UIF: Update interrupt flag;
    {
         //g_tick++; 
    }
    TIM2_SR &= ~(uint32_t)(1 <<0 );
}
void delay_ms(uint32_t ms)
{

    TIM2_PSC = 7999;
    TIM2_ARR = ms;
    TIM2_CNT  = 0;
    TIM2_CR1 |= (1 << 0);
    while(TIM2_CNT < ms) {}
    TIM2_CR1 &= ~(uint32_t)(1 << 0);
    TIM2_CNT = 0;
}

void TIM3_init_IT(void)
{
    TIM3_PSC = 7999;                   // Prescaler
    TIM3_ARR = 999;                    // Auto Reload
    TIM3_CNT = 0;
    TIM3_SR &= ~(uint32_t)(1 << 0);    // Clear UIF flag
    TIM3_DIER |= (1 << 0);             // Update Interrupt Enable
    TIM3_CR1 |= (1 << 0);              // Counter Enable
    NVIC_ISER0 |= (1 << 29);           // Enable TIM3 IRQ
}

void TIM3_IRQHandler(void)
{
    if(TIM3_SR & (1 << 0))
    {
        TIM3_SR &= ~(uint32_t)(1 << 0);

        g_UpdateDisplayFlag = 1;
    }
}
