#include "I2C.h"          // own header ¡ª already present
#include "RCC.h"          // RCC_Enable_PortB, RCC_Enable_AFIO, RCC_Enable_TIM2
#include "GPIO.h"         // GPIO_Config


void 	I2C_Init(void)
{
    RCC_Enable_PortB();
    RCC_Enable_AFIO();
    RCC_Enable_TIM2();

    GPIO_Config(GPIOB,GPIO_PIN_6,GPIO_MODE_AF_OD);
    GPIO_Config(GPIOB,GPIO_PIN_7,GPIO_MODE_AF_OD);
    I2C1_CR1   &= ~(uint32_t)(1<< 0);                // disable
    I2C1_CR2 = 8;                                    // on clock 8mhz
    I2C1_CCR = 40;                                   //contro SCL in master mode flow 8mhz
    I2C1_TRISE = 9;                                  //  chot clock
    I2C1_CR1   |=  (1<< 0);                          ///Peripheral enable
}

void I2C_Start(void)
{
    I2C1_CR1 &= ~(uint32_t)(1 << 9);
    I2C1_CR1 |= (1 << 8);
    while(!(I2C1_SR1 & 0x01))
    {

    }
    //Doing sth
}
void  I2C_Stop(void)
{
    I2C1_CR1 |= (1<<9);
}
void  I2C_Send_Addr(uint8_t addr, uint8_t rw)
{
    I2C1_DR = (uint32_t)((addr << 1) | (rw & 0x01));
    while(!(I2C1_SR1 &(1<<1)))
    {
    }
    (void)I2C1_SR2;
}
uint8_t I2C_Send_Data(uint8_t data)
{
    I2C1_DR = data;
    while(!(I2C1_SR1 &(1 << 2))) {}                 // ACK down seccuss. on fail
    if(I2C1_SR1 & (1 << 10))                        //  check NACK //ACK
    {
        I2C1_SR1 &= ~(uint32_t)(1 << 10);
        I2C_Stop();
        return 1;                                  // fail
    }
    return 0;                                      // success
}
uint8_t I2C_Read_Data(uint8_t ack)
{
    if(ack)
    {
        I2C1_CR1 |= (1<< 10);                       // ack = 1;
    }
    else
    {
        I2C1_CR1 &= ~(uint32_t)(1<< 10);            //ack = 0
    }
    while(!(I2C1_SR1 &(1 << 6))) {}                 // check RT
    return(uint8_t)I2C1_DR;
}




