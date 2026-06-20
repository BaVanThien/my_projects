
#include "DS3231.h"
#include "I2C.h"
uint8_t bcd_to_dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10 + (bcd & 0x0F));
}
uint8_t dec_to_bcd(uint8_t dec)
{
    return (uint8_t)(((dec/10) << 4) | (dec % 10));
}

void DS3231_Set_Time(uint8_t hour, uint8_t min, uint8_t sec)
{
    I2C_Start();
    I2C_Send_Addr(0x68, 0);
    uint8_t status = 0;
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
void DS3231_Get_Time(uint8_t *hour,  uint8_t *min, uint8_t *sec)
{
    I2C_Start();
    I2C_Send_Addr(0x68, 0);
    I2C_Send_Data(0x00);

    I2C_Start();
    I2C_Send_Addr(0x68, 1);
    *sec = bcd_to_dec(I2C_Read_Data(1));
    *min = bcd_to_dec(I2C_Read_Data(1));
    *hour = bcd_to_dec(I2C_Read_Data(0));
}
