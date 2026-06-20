#include "display.h"

void safeDrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    xSemaphoreTake(xLcdMutex, portMAX_DELAY);
    drawPixel((uint8_t)x, (uint8_t)y, color);
    xSemaphoreGive(xLcdMutex);
}

void drawPixelBlock(uint8_t x, uint8_t y, uint16_t color)
{
    for (int dx = 0; dx < 2; dx++)
        for (int dy = 0; dy < 2; dy++)
            safeDrawPixel((uint16_t)(x * 2 + dx), (uint16_t)(y * 2 + dy), color);
}

void drawFood(void)
{
    drawPixelBlock(food.x, food.y, 0xF800);
}
void drawHead(Point p)
{
    drawPixelBlock(p.x, p.y, 0x07E0);
}
void clearTail(Point tail)
{
    drawPixelBlock(tail.x, tail.y, 0x0000);
}
