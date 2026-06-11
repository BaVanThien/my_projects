//#include "TFT.h"
//#include"main.h"

//#include"String.h"


//void writeCMDTFT(uint8_t cmd)
//{
//    GPIO_Write_Pin(PORT_CS, PIN_CS, 0); // CS = 0
//    GPIO_Write_Pin(PORT_A0, PIN_A0, 0); // A0 = 0 -> CMD
//    SPI1_Send(cmd);
//    GPIO_Write_Pin(PORT_CS, PIN_CS, 1); // CS = 1
//}

//void writeDataTFT(uint8_t data)
//{
//    GPIO_Write_Pin(PORT_CS, PIN_CS, 0);
//    GPIO_Write_Pin(PORT_A0, PIN_A0, 1); // A0 = 1 -> DATA
//    SPI1_Send(data);
//    GPIO_Write_Pin(PORT_CS, PIN_CS, 1);
//}

//void sendCMDList(const uint8_t* cmdList)
//{
//    uint8_t index = 0;
//    uint8_t cmd = 0;
//    uint8_t num = 0;

//    while(1)
//    {
//        cmd = *cmdList++;
//        num = *cmdList++;
//        if(cmd == LCD_CMD_END)
//        {
//            break;
//        }
//        else
//        {
//            writeCMDTFT(cmd);
//            for(index = 0; index < num ; index++)
//            {
//                writeDataTFT(*cmdList++);
//            }
//        }
//    }
//}

//void setPos(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
//{
//    writeCMDTFT(0x2A);
//    writeDataTFT(0x00);
//    writeDataTFT(x1);
//    writeDataTFT(0x00);
//    writeDataTFT(x2);
//    writeCMDTFT(0x2B);
//    writeDataTFT(0x00);
//    writeDataTFT(y1);
//    writeDataTFT(0x00);
//    writeDataTFT(y2);
//}
////RGB 16bit 565
//void fullDisplay(uint16_t color)
//{
//    setPos(0, 0, 127, 159);
//    writeCMDTFT(0x2C);
//    for(int i = 0 ; i < 128*160; i++)
//    {
//        writeDataTFT(color & 0xFF);
//        writeDataTFT(color >> 8);
//    }
//}


//void drawPixel(uint8_t x, uint8_t y, uint16_t color)
//{
//    if(x >= 128 || y >= 160)
//    {
//        return ;
//    }
//    setPos(x,y,x+1,y+1);
//    writeCMDTFT(0x2C);
//    writeDataTFT(color & 0xFF);
//    writeDataTFT(color >> 8);
//}

//void fillRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
//{
//    setPos(x1, y1, x2, y2);
//    writeCMDTFT(0x2C);
//    for(int i = 0; i < (x2-x1+1) * (y2-y1+1); i++)
//    {
//        writeDataTFT(color & 0xFF);
//        writeDataTFT(color >> 8);
//    }
//}

//void initTFT(void)
//{
//    GPIO_Config(PORT_A0, PIN_A0, GPIO_MODE_OUTPUT_PP);
//    GPIO_Config(PORT_CS, PIN_CS, GPIO_MODE_OUTPUT_PP);
//    GPIO_Config(PORT_RESET, PIN_RESET, GPIO_MODE_OUTPUT_PP);
//    // HW RESET
//    GPIO_Write_Pin(PORT_RESET, PIN_RESET,0);
//    delay_ms(20);
//    GPIO_Write_Pin(PORT_RESET, PIN_RESET,1);
//    delay_ms(150);
//    //SW RESET
//    writeCMDTFT(0x01);
//    delay_ms(150);
//    // Sleep out
//    writeCMDTFT(0x11);
//    delay_ms(255);

//    sendCMDList(u8InitCmdList);

//    writeCMDTFT(0x36); // Memory Data Access Control
//    writeDataTFT(0x08);

//    writeCMDTFT(0x3A); // Interface Pixel Format
//    writeDataTFT(0x05);

//    writeCMDTFT(0x20); // Display inversion off

//    setPos(0,0,128,160);

//    // EN DISPLAY
//    writeCMDTFT(0x29);
//    delay_ms(100);

//}

//void drawChar(uint8_t x, uint8_t y, uint8_t ch, FontDef font, uint16_t color, uint16_t bg)
//{
//    uint8_t i,j;
//    uint16_t pixelData;
//    setPos(x, y, x + font.width - 1, y + font.height - 1); // Place one area at a time.
//    writeCMDTFT(0x2C);
//    for(i = 0; i < font.height; i++)
//    {
//        pixelData = font.data[(ch - 32)*font.height + i];
//        for(j = 0; j < font.width; j++)
//        {
//            uint16_t c = ((pixelData << j) & 0x8000) ? color : bg;
//            writeDataTFT(c & 0xFF);                        // sending data consecutively
//            writeDataTFT(c >> 8);
//        }
//    }
//}



//void drawString(uint8_t x, uint8_t y, uint8_t *str, FontDef font, uint16_t color, uint16_t bg)
//{
//    while(*str)
//    {
//        drawChar(x,y,*str,font,color,bg);
//        x+= font.width;
//        str++;
//    }
//}



//void Display_Time_Digit(uint8_t x, uint8_t y, uint16_t number, FontDef font, uint16_t color, uint16_t bg)
//{
//    char str[5];                                            // string 2 character and \0'

//    number_to_character_t((uint8_t)number, (uint8_t*)str, 2);
//    str[2] = '\0';                                           // end character

//    drawString(x, y, (uint8_t*)str, font, color, bg);
//}

//void Update_Time_Top(void)
//{
//    // Ve gio o tren (y=50) - can giua
//    Display_Time_Digit(36, 50, rtc_h, Font_7x10, 0xFFFF, 0x1098);
//    drawString(50, 50, (uint8_t*)":", Font_7x10, 0xFFFF, 0x1098);
//    Display_Time_Digit(57, 50, rtc_m, Font_7x10, 0xFFFF, 0x1098);
//    drawString(71, 50, (uint8_t*)":", Font_7x10, 0xFFFF, 0x1098);
//    Display_Time_Digit(78, 50, rtc_s, Font_7x10, 0xFFFF, 0x1098);
//}

//void Update_Date_Top(void)
//{
//    // Ve ngay o tren (y=50) - can giua
//    Display_Time_Digit(36, 50, rtc_d, Font_7x10, 0xFFFF, 0x1098);
//    drawString(50, 50, (uint8_t*)"/", Font_7x10, 0xFFFF, 0x1098);
//    Display_Time_Digit(57, 50, rtc_mt, Font_7x10, 0xFFFF, 0x1098);
//    drawString(71, 50, (uint8_t*)"/", Font_7x10, 0xFFFF, 0x1098);
//    Display_Time_Digit(78, 50, rtc_y, Font_7x10, 0xFFFF, 0x1098);
//}

//void Update_Date_Bottom(void)
//{
//    // Ve ngay o duoi (y=70) - can giua
//    Display_Time_Digit(36, 70, rtc_d, Font_7x10, 0xFFE0, 0x1098);
//    drawString(50, 70, (uint8_t*)"/", Font_7x10, 0xFFE0, 0x1098);
//    Display_Time_Digit(57, 70, rtc_mt, Font_7x10, 0xFFE0, 0x1098);
//    drawString(71, 70, (uint8_t*)"/", Font_7x10, 0xFFE0, 0x1098);
//    Display_Time_Digit(78, 70, rtc_y, Font_7x10, 0xFFE0, 0x1098);
//}


//void Update_Clock_Display(void)
//{
//    if (g_DisplayStatus == DISPLAY_STATUS_OFF)
//    {
//        return;
//    }

//    if (g_IsTimeSynced == 1)
//    {
//        DS3231_Get_Time(&rtc_h, &rtc_m, &rtc_s);
//        DS3231_Get_Day(&rtc_d, &rtc_mt, &rtc_y);
//    }
//    else
//    {
//        rtc_h = 0;
//        rtc_m = 0;
//        rtc_s = 0;
//        rtc_d = 1;
//        rtc_mt = 1;
//        rtc_y = 26;
//    }

//    if (g_DisplayMode == DISPLAY_MODE_TIME)
//    {
//        // Hien thi gio o tren + ngay o duoi (mac dinh luc khoi dong)
//        fillRect(28, 45, 100, 65, 0x1098);
//        Update_Time_Top();
//        Update_Date_Bottom();
//    }
//    else if (g_DisplayMode == DISPLAY_MODE_DATE)
//    {
//        // Chi hien thi ngay o tren, xoa gio o tren
//        fillRect(28, 45, 100, 65, 0x1098);
//        Update_Date_Top();
//        Update_Date_Bottom();
//    }

//}

//void Update_Clock_Display_Silent(void)
//{
//    if (g_DisplayStatus == DISPLAY_STATUS_OFF) return;

//    if (g_IsTimeSynced == 1)
//    {
//        DS3231_Get_Time(&rtc_h, &rtc_m, &rtc_s);
//        DS3231_Get_Day(&rtc_d, &rtc_mt, &rtc_y);
//    }
//    else
//    {
//        rtc_h = 0;
//        rtc_m = 0;
//        rtc_s = 0;
//        rtc_d = 1;
//        rtc_mt = 1;
//        rtc_y = 26;
//    }

//    if (g_DisplayMode == DISPLAY_MODE_TIME)
//    {
//        Update_Time_Top();
//        Update_Date_Bottom();
//    }
//    else if (g_DisplayMode == DISPLAY_MODE_DATE)
//    {
//        Update_Date_Top();
//        Update_Date_Bottom();
//    }
//}



/* =========================================================
 *  TFT.c ¡ª TFT ST7735 display driver over SPI
 *
 *  Contains: pure driver only (write/draw/init)
 *  Clock display logic has been moved to Core/Display_task.c
 *
 *  Dependencies:
 *    - TFT.h  : prototypes + defines
 *    - SPI.h  : SPI1_Send
 *    - GPIO.h : GPIO_Write_Pin, GPIO_Config
 *    - Tim.h  : delay_ms
 * ========================================================= */


#include "TFT.h"          // own header
#include "SPI.h"          // SPI1_Send
#include "GPIO.h"         // GPIO_Config, GPIO_Write_Pin
#include "Tim.h"          // delay_ms
#include "FONT.h"         // FontDef


/* =========================================================
 *  SEND COMMAND / DATA
 * ========================================================= */
void writeCMDTFT(uint8_t cmd)
{
    GPIO_Write_Pin(PORT_CS, PIN_CS, 0);
    GPIO_Write_Pin(PORT_A0, PIN_A0, 0); // A0=0 -> CMD
    SPI1_Send(cmd);
    GPIO_Write_Pin(PORT_CS, PIN_CS, 1);
}

void writeDataTFT(uint8_t data)
{
    GPIO_Write_Pin(PORT_CS, PIN_CS, 0);
    GPIO_Write_Pin(PORT_A0, PIN_A0, 1); // A0=1 -> DATA
    SPI1_Send(data);
    GPIO_Write_Pin(PORT_CS, PIN_CS, 1);
}

/* =========================================================
 *  SEND INIT COMMAND LIST
 * ========================================================= */
void sendCMDList(const uint8_t* cmdList)
{
    uint8_t index = 0;
    uint8_t cmd   = 0;
    uint8_t num   = 0;

    while (1)
    {
        cmd = *cmdList++;
        num = *cmdList++;
        if (cmd == LCD_CMD_END) break;

        writeCMDTFT(cmd);
        for (index = 0; index < num; index++)
        {
            writeDataTFT(*cmdList++);
        }
    }
}

/* =========================================================
 *  SET DRAW REGION (coordinate window)
 * ========================================================= */
void setPos(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    writeCMDTFT(0x2A);
    writeDataTFT(0x00); writeDataTFT(x1);
    writeDataTFT(0x00); writeDataTFT(x2);

    writeCMDTFT(0x2B);
    writeDataTFT(0x00); writeDataTFT(y1);
    writeDataTFT(0x00); writeDataTFT(y2);
}

/* =========================================================
 *  FILL ENTIRE SCREEN
 * ========================================================= */
void fullDisplay(uint16_t color)
{
    setPos(0, 0, 127, 159);
    writeCMDTFT(0x2C);
    for (int i = 0; i < 128 * 160; i++)
    {
        writeDataTFT(color & 0xFF);
        writeDataTFT(color >> 8);
    }
}

/* =========================================================
 *  DRAW 1 PIXEL
 * ========================================================= */
void drawPixel(uint8_t x, uint8_t y, uint16_t color)
{
    if (x >= 128 || y >= 160) return;
    setPos(x, y, x + 1, y + 1);
    writeCMDTFT(0x2C);
    writeDataTFT(color & 0xFF);
    writeDataTFT(color >> 8);
}

/* =========================================================
 *  FILL RECTANGLE
 * ========================================================= */
void fillRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
{
    setPos(x1, y1, x2, y2);
    writeCMDTFT(0x2C);
    for (int i = 0; i < (x2 - x1 + 1) * (y2 - y1 + 1); i++)
    {
        writeDataTFT(color & 0xFF);
        writeDataTFT(color >> 8);
    }
}

/* =========================================================
 *  INIT DISPLAY
 * ========================================================= */
void initTFT(void)
{
    GPIO_Config(PORT_A0,    PIN_A0,    GPIO_MODE_OUTPUT_PP);
    GPIO_Config(PORT_CS,    PIN_CS,    GPIO_MODE_OUTPUT_PP);
    GPIO_Config(PORT_RESET, PIN_RESET, GPIO_MODE_OUTPUT_PP);

    // HW RESET
    GPIO_Write_Pin(PORT_RESET, PIN_RESET, 0);
    delay_ms(20);
    GPIO_Write_Pin(PORT_RESET, PIN_RESET, 1);
    delay_ms(150);

    // SW RESET
    writeCMDTFT(0x01);
    delay_ms(150);

    // Sleep out
    writeCMDTFT(0x11);
    delay_ms(255);

    sendCMDList(u8InitCmdList);

    writeCMDTFT(0x36); writeDataTFT(0x08); // Memory Data Access Control
    writeCMDTFT(0x3A); writeDataTFT(0x05); // Interface Pixel Format
    writeCMDTFT(0x20);                      // Display inversion off

    setPos(0, 0, 128, 160);

    writeCMDTFT(0x29); // Enable display
    delay_ms(100);
}

/* =========================================================
 *  DRAW 1 CHARACTER
 * ========================================================= */
void drawChar(uint8_t x, uint8_t y, uint8_t ch,
              FontDef font, uint16_t color, uint16_t bg)
{
    uint8_t  i, j;
    uint16_t pixelData;

    setPos(x, y, x + font.width - 1, y + font.height - 1);
    writeCMDTFT(0x2C);

    for (i = 0; i < font.height; i++)
    {
        pixelData = font.data[(ch - 32) * font.height + i];
        for (j = 0; j < font.width; j++)
        {
            uint16_t c = ((pixelData << j) & 0x8000) ? color : bg;
            writeDataTFT(c & 0xFF);
            writeDataTFT(c >> 8);
        }
    }
}

/* =========================================================
 *  DRAW STRING
 * ========================================================= */
void drawString(uint8_t x, uint8_t y, uint8_t *str,
                FontDef font, uint16_t color, uint16_t bg)
{
    while (*str)
    {
        drawChar(x, y, *str, font, color, bg);
        x += font.width;
        str++;
    }
}


