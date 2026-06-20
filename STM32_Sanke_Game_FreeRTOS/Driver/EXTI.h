#ifndef __EXTI_H
#define __EXTI_H

#include<stdint.h>
#include"TYPE.h"
#include"AFIO.h"
#include"CPIO.h"


#define NVIC_ISER1 *((uint32_t*)(0xE000E104UL))




#define EXTI_RISING_MODE 0x00
#define EXTI_FALLING_MODE 0x01
#define EXTI_BOTH_MODE 0x02
typedef struct
{
    __32BIT IMR;
    __32BIT EMR;
    __32BIT RTSR;
    __32BIT FTSR;
    __32BIT SWIER;
    __32BIT PR;
} EXTI_Typedef;


void EXIT0_Init(void);
//void EXIT_Init(uint16_t GPIO_Pin, GPIOx_Typef *Port, uint8_t type);
void EXIT_Config_Expert(GPIO_Typedef *port, uint8_t gpio_pin,uint8_t type);
uint8_t get_Pin_Number(uint16_t gpio_pin);
void EXTI0_IRQHandler(void);
void RCC_Enable_AFIO(void);
void NVIC_Enable_EXTI(uint8_t pin);
void NVIC_UART_En(void);
void NVIC_USB_En(void);

//#define EXTI ((volatile EXTI_Typedef *) 0x40010400UL)
#define EXTI  ((volatile EXTI_Typedef*)0x40010400UL)
#endif



