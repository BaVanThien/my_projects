#ifndef __MAIN_H
#define __MAIN_H

//lib.c

#include<stdint.h>
#include<stdlib.h>    


//driver, core
#include "RCC.h"
#include "CPIO.h"
#include "SPI.h"
#include "Tim.h"
#include "I2C.h"
#include "EXTI.h"
#include "TYPE.h"
#include "UART.h"
#include "TFT.h"

//RTOS code
#include "FreeRTOS.h"
#include "projdefs.h"
#include "event_groups.h"
#include "task.h"
#include "semphr.h"

//void Test(void *param);
//void Test2(void *param);
#endif
