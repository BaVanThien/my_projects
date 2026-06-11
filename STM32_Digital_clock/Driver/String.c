#include "String.h"


void number_to_character_t(uint8_t value, uint8_t data[], uint8_t index)
{
    while(value != 0)
    {
        uint16_t du;
        du = value % 10;
        data[index - 1] =(uint8_t)du + '0';
        index--;
        value = value/10;
    }
    while(index != 0)
    {
        data[index - 1] = '0';
        index--;
    }
}

uint16_t character_to_number(uint8_t data[], uint8_t index)
{
    uint16_t value = 0;
    for (uint8_t i = 0; i < index; i++)
    {
        uint8_t temp = data[i] - '0';
        value = value*10 + temp;
    }
    return value;
}


