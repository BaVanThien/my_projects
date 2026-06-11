#include <stdint.h>
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"


void main()
{
    RCC_Enable_TIM2();
    RCC_Enable_PortA();
    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP);

    while (1)
    {
        GPIO_Write_Pin(GPIOA, GPIO_PIN_0, 1);
        delay_ms(1000);
        GPIO_Write_Pin(GPIOA, GPIO_PIN_0, 0);
        delay_ms(1000);
    }
}