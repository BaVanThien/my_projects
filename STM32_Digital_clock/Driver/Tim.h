#ifndef __TIM_H
#define __TIM_H
#include<stdint.h>


#define   TIM2_ADD_BASE  0x40000000UL

#define    TIM2_CR1        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x00))
#define    TIM2_CR2        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x04))  
#define    TIM2_SMCR       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x08))  
#define    TIM2_DIER       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x0C))  
#define    TIM2_SR         (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x10)) 
#define    TIM2_EGR        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x14))  
#define    TIM2_CCMR1      (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x18))  
#define    TIM2_CCMR2      (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x1C))  
#define    TIM2_CCER       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x20))  
#define    TIM2_CNT        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x24))  	
#define    TIM2_PSC        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x28))
#define    TIM2_ARR        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x2C))
#define    TIM2_CCR1       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x34))
#define    TIM2_CCR2       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x38))
#define    TIM2_CCR3       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x3C))	
#define    TIM2_CCR4       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x40))	
#define    TIM2_DCR        (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x48))
#define    TIM2_DMAR       (*(volatile uint32_t*)(TIM2_ADD_BASE + 0x4C)) 
	
#define TIM3_ADD_BASE  0x40000400UL

#define TIM3_CR1   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x00))
#define TIM3_CR2   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x04))
#define TIM3_SMCR  (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x08))
#define TIM3_DIER  (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x0C))
#define TIM3_SR    (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x10))
#define TIM3_EGR   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x14))
#define TIM3_CNT   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x24))
#define TIM3_PSC   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x28))
#define TIM3_ARR   (*(volatile uint32_t*)(TIM3_ADD_BASE + 0x2C))

typedef struct
{
	 uint8_t second;
	 uint8_t minute;
	 uint8_t hour;
} Time_number_type;
static Time_number_type time_n;

typedef struct
{
	uint8_t second[2];
	uint8_t minute[2];
	uint8_t hour[2];
} Time_uint8_t_type;
static  Time_uint8_t_type time_c;

typedef struct 
{
	uint8_t day;
	uint8_t month;
	uint8_t year;
} Date_number_type;
static Date_number_type date_n;                                         

typedef struct 
{
	uint8_t day[2];
	uint8_t month[2];
	uint8_t year[4];
} Date_uint8_t_type;
static  Date_uint8_t_type date_c;

	
void TIM2_init_IT(void);
void TIM2_IRQHandler(void); 
extern volatile uint8_t blink_status;
void delay_ms(uint32_t ms);
void TIM3_init_IT(void);
void TIM3_IRQHandler(void);

#endif



