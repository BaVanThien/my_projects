#include"Tim.h"
#include"EXTI.h"

// Fsty = 8000mhz
//        Fsty      8000
//  f =  ------- =  ------- = 1mhz = 1000 stick each secon, 1ms 1 styck
//       PSC + 1    8000
//        1
//   t = ----
//        f

volatile uint8_t blink_status = 0;
/*
void TIM2_init_IT(void){
	TIM2_PSC = 7999;//39999; //7999;//TIMx prescale//1000 step each seccon/ 1 ms is step
  TIM2_ARR = 999;	       // Auto-Reload Register//
	TIM2_DIER |= (1 << 0);// Trigger interrupt enable,Interrupt enable register
	TIM2_CR1  |= (1 << 0);  // TIMx control register 1 CEN: Conter enable
	TIM2_SR &= ~(uint32_t)(1 << 0);
	NVIC_ISER0 |= (1 << 28);
}*/
//TIM2_SR & 0x01

void TIM2_IRQHandler(void)
{
    if(TIM2_SR & 0x01)     //UIF: Update interrupt flag;
    {
        if(blink_status == 1)
        {
            blink_status = 0;
        }
        else
        {
            blink_status = 1;
        }
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


