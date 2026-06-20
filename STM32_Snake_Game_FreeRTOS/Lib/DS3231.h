#ifndef __DS3231_H
#define __DS3231_H
#include "stdint.h"

uint8_t bcd_to_dec(uint8_t bcd);
uint8_t dec_to_bcd(uint8_t dec);
void DS3231_Set_Time( uint8_t hour, uint8_t min,uint8_t sec);
void DS3231_Get_Time(uint8_t *hour,  uint8_t *min, uint8_t *sec);

#endif

