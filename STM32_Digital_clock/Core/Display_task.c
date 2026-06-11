/* =========================================================
 *  Display_task.c
 *  Clock display logic 
 *
 *  Dependencies:
 *    - main.h    : global variables (g_DisplayStatus, g_DisplayMode, rtc_*, flags)
 *    - TFT.h     : drawString, fillRect, fullDisplay (pure TFT driver)
 *    - DS3231.h  : DS3231_Get_Time, DS3231_Get_Day
 *    - FONT.h    : FontDef, Font_7x10
 *    - String.h  : number_to_character_t
 * ========================================================= */

#include "Display_task.h" 
#include "main.h"         
#include "TFT.h"          
#include "DS3231.h"      
#include "FONT.h"         
#include "String.h"    

/* =========================================================
 *  DISPLAY A 2-DIGIT NUMBER (hour/minute/second/day/month/year)
 * ========================================================= */
void Display_Time_Digit(uint8_t x, uint8_t y, uint16_t number,
                        FontDef font, uint16_t color, uint16_t bg)
{
    char str[3];
    number_to_character_t((uint8_t)number, (uint8_t*)str, 2);
    str[2] = '\0';
    drawString(x, y, (uint8_t*)str, font, color, bg);
}

/* =========================================================
 *  DRAW TIME IN TOP REGION (y=50)
 * ========================================================= */
void Update_Time_Top(void)
{
    Display_Time_Digit(36, 50, rtc_h, Font_7x10, 0xFFFF, 0x1098);
    drawString(50, 50, (uint8_t*)":", Font_7x10, 0xFFFF, 0x1098);
    Display_Time_Digit(57, 50, rtc_m, Font_7x10, 0xFFFF, 0x1098);
    drawString(71, 50, (uint8_t*)":", Font_7x10, 0xFFFF, 0x1098);
    Display_Time_Digit(78, 50, rtc_s, Font_7x10, 0xFFFF, 0x1098);
}

/* =========================================================
 *  DRAW DATE IN TOP REGION (y=50)
 * ========================================================= */
void Update_Date_Top(void)
{
    Display_Time_Digit(36, 50, rtc_d,  Font_7x10, 0xFFFF, 0x1098);
    drawString(50, 50, (uint8_t*)"/",  Font_7x10, 0xFFFF, 0x1098);
    Display_Time_Digit(57, 50, rtc_mt, Font_7x10, 0xFFFF, 0x1098);
    drawString(71, 50, (uint8_t*)"/",  Font_7x10, 0xFFFF, 0x1098);
    Display_Time_Digit(78, 50, rtc_y,  Font_7x10, 0xFFFF, 0x1098);
}

/* =========================================================
 *  DRAW DATE IN BOTTOM REGION (y=70)
 * ========================================================= */
void Update_Date_Bottom(void)
{
    Display_Time_Digit(36, 70, rtc_d,  Font_7x10, 0xFFE0, 0x1098);
    drawString(50, 70, (uint8_t*)"/",  Font_7x10, 0xFFE0, 0x1098);
    Display_Time_Digit(57, 70, rtc_mt, Font_7x10, 0xFFE0, 0x1098);
    drawString(71, 70, (uint8_t*)"/",  Font_7x10, 0xFFE0, 0x1098);
    Display_Time_Digit(78, 70, rtc_y,  Font_7x10, 0xFFE0, 0x1098);
}

/* =========================================================
 *  FETCH RTC DATA ！ shared by both Update functions below
 * ========================================================= */
static void Fetch_RTC_Data(void)
{
    if (g_IsTimeSynced == 1)
    {
        DS3231_Get_Time(&rtc_h, &rtc_m, &rtc_s);
        DS3231_Get_Day(&rtc_d, &rtc_mt, &rtc_y);
    }
    else
    {
        rtc_h = 0;  rtc_m = 0;  rtc_s = 0;
        rtc_d = 1;  rtc_mt = 1; rtc_y = 26;
    }
}

/* =========================================================
 *  FULL SCREEN UPDATE (clears background ！ used on display wake)
 * ========================================================= */
void Update_Clock_Display(void)
{
    if (g_DisplayStatus == DISPLAY_STATUS_OFF) return;

    Fetch_RTC_Data();

    fillRect(28, 45, 100, 65, 0x1098); // clear top region

    if (g_DisplayMode == DISPLAY_MODE_TIME)
    {
        Update_Time_Top();
        Update_Date_Bottom();
    }
    else
    {
        Update_Date_Top();
        Update_Date_Bottom();
    }
}

/* =========================================================
 *  SILENT UPDATE (no background clear ！ called from TIM3)
 * ========================================================= */
void Update_Clock_Display_Silent(void)
{
    if (g_DisplayStatus == DISPLAY_STATUS_OFF) return;

    Fetch_RTC_Data();

    if (g_DisplayMode == DISPLAY_MODE_TIME)
    {
        Update_Time_Top();
        Update_Date_Bottom();
    }
    else
    {
        Update_Date_Top();
        Update_Date_Bottom();
    }
}

/* =========================================================
 *  FULL SCREEN REFRESH (display on/off)
 * ========================================================= */
void Display_RefreshScreen(void)
{
    if (g_DisplayStatus == DISPLAY_STATUS_OFF)
    {
        fullDisplay(0x0000); // off ！ fill black
    }
    else
    {
        fullDisplay(0xF800); // on ！ fill background
        Update_Clock_Display();
    }
}

/* =========================================================
 *  TOGGLE DISPLAY MODE (button: switch time/date view)
 * ========================================================= */
void Display_ChangeMode(void)
{
    if (g_DisplayMode == DISPLAY_MODE_TIME)
    {
        Update_Time_Top();
        Update_Date_Bottom();
    }
    else
    {
        Update_Date_Top();
        Update_Date_Bottom();
    }
}

/* =========================================================
 *  MAIN TASK ！ called in while(1)
 * ========================================================= */
void Display_Task(void)
{
    if (g_ScreenChangedFlag)
    {
        g_ScreenChangedFlag = 0;
        Display_RefreshScreen();
    }
    else if (g_DisplayModeToggleFlag && (g_DisplayStatus == DISPLAY_STATUS_ON))
    {
        // BUG FIX: old condition "&& DISPLAY_STATUS_ON" was always true
        // Fixed to: "g_DisplayStatus == DISPLAY_STATUS_ON"
        g_DisplayModeToggleFlag = 0;
        Display_ChangeMode();
    }
    else if (g_UpdateDisplayFlag)
    {
        g_UpdateDisplayFlag = 0;
        Update_Clock_Display_Silent(); // TIM3
    }
}
