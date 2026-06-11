#include "DS3231.h"
#include "I2C.h"





uint8_t bcd_to_dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10 + (bcd & 0x0F));// 10: decimail ex: 4 * 10 * +  5; = 45;
}
uint8_t dec_to_bcd(uint8_t dec)
{
    return (uint8_t)(((dec/10) << 4) | (dec % 10));   // 45 :  4 | 5
}

void DS3231_Set_Time(uint8_t hour, uint8_t min, uint8_t sec)
{
    uint8_t status = 0;
    I2C_Start();
    I2C_Send_Addr(0x68, 0);
    status = I2C_Send_Data(0x00);
    if(status)
    {
        return ;  //Need check
    }
    status = I2C_Send_Data(dec_to_bcd(sec));
    if(status)
    {
        return ;  //Need check
    }
    status = I2C_Send_Data(dec_to_bcd(min));
    if(status)
    {
        return ;  //Need check
    }
    status = I2C_Send_Data(dec_to_bcd(hour));
    if(status)
    {
        return ;  //Need check
    }

    I2C_Stop();
}
void DS3231_Set_Day(uint8_t day, uint8_t month, uint8_t year)
{
    uint8_t status = 0;
    I2C_Start();
    I2C_Send_Addr(0x68, 0);
    status = I2C_Send_Data(0x04);
    status = I2C_Send_Data(dec_to_bcd(day));
    if(status)
    {
        return ;  //Need check
    }
    status = I2C_Send_Data(dec_to_bcd(month));
    if(status)
    {
        return ;  //Need check
    }
    status = I2C_Send_Data(dec_to_bcd(year));
    if(status)
    {
        return ;  //Need check
    }
    I2C_Stop();
}
void DS3231_Get_Time(volatile uint8_t *hour, volatile uint8_t *min, volatile uint8_t *sec)
{
    I2C_Start();
    I2C_Send_Addr(0x68, 0);//  write
    I2C_Send_Data(0x00);

    I2C_Start();
    I2C_Send_Addr(0x68, 1);// read
    *sec = bcd_to_dec(I2C_Read_Data(1));
    *min = bcd_to_dec(I2C_Read_Data(1));
    *hour = bcd_to_dec(I2C_Read_Data(0));

}

void DS3231_Get_Day(volatile uint8_t *day, volatile uint8_t *month, volatile uint8_t *year)
{
    I2C_Start();
    I2C_Send_Addr(0x68, 0); //write
    I2C_Send_Data(0x04);    // register start

    I2C_Start();
    I2C_Send_Addr(0x68, 1); //read
    *day = bcd_to_dec(I2C_Read_Data(1));
    *month = bcd_to_dec(I2C_Read_Data(1));
    *year = bcd_to_dec(I2C_Read_Data(0));
}
