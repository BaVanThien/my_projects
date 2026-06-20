#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "game_logic.h" 

extern SemaphoreHandle_t xLcdMutex;

void safeDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void drawPixelBlock(uint8_t x, uint8_t y, uint16_t color);
void drawFood(void);
void drawHead(Point p);
void clearTail(Point tail);

#endif /* DISPLAY_H */


