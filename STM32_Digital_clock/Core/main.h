#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>




/* ========================================================================== */
//(SYSTEM CONFIGURATION & BUFFERS)               */
/* ========================================================================== */
 
#define DMA_BUF_SIZE     30
#define RING_BUF_SIZE    50
#define BUFFER_SIZE      30

/* ========================================================================== */
//  (TYPEDEF ENUM/STRUCT)               
/* ========================================================================== */
typedef enum {
    DISPLAY_MODE_TIME, 
    DISPLAY_MODE_DATE  
} DisplayMode_t;

typedef enum {
    DISPLAY_STATUS_OFF,
    DISPLAY_STATUS_ON
} DisplayStatus_t;


/* ========================================================================== */
// EXTERN VARIABLES                  
/* ========================================================================== */
extern volatile DisplayMode_t g_DisplayMode;
extern volatile DisplayStatus_t g_DisplayStatus;
extern volatile uint8_t g_ScreenChangedFlag;
extern volatile uint8_t g_DisplayModeToggleFlag;
extern volatile uint8_t g_Button1PressedFlag;
extern volatile uint8_t g_Button2PressedFlag;
extern volatile uint8_t g_IsTimeSynced;
extern volatile uint8_t rtc_h, rtc_m, rtc_s;
extern volatile uint8_t rtc_d, rtc_mt,rtc_y; 
extern uint8_t RxBuffer[BUFFER_SIZE];
extern uint8_t RingBuffer[RING_BUF_SIZE];
extern uint8_t DmaBuffer[DMA_BUF_SIZE];
extern volatile uint8_t g_UpdateDisplayFlag;

/* ========================================================================== */
// PROTOTYPE
/* ========================================================================== */
void System_Clock_Init(void);

#endif
 



