#ifndef __STRING_H
#define __STRING_H
#include <stdint.h>

uint16_t character_to_number(uint8_t data[], uint8_t index);
void number_to_character_t(uint8_t value, uint8_t data[], uint8_t index);

void Send_Time_To_PC(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t month, uint8_t y);
#endif
