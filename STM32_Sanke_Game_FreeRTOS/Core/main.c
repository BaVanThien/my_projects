#include "main.h"
#include "game_logic.h"
#include "display.h"
#include "button.h"
#include "task_snake.h"
#include "task_input.h"

/* ---------- RTOS OBJECTS DEFINITION ---------- */
/* Declared as extern in game_logic.h ----------- */
SemaphoreHandle_t  xSnakeMutex;
SemaphoreHandle_t  xLcdMutex;
EventGroupHandle_t xDirectionEvent;

/* ---------- MAIN ---------- */
int main(void)
{
    /* Enable peripheral clocks */
    RCC_Enable_PortA();
    RCC_Enable_PortB();
    RCC_Enable_SPI1();
    RCC_Enable_AFIO();
    RCC_Enable_TIM2();

    /* Initialize peripherals */
    SPI1_Init_Master();
    initTFT();
    fullDisplay(0x0000);
    Button_Init();

    /*  Create RTOS objects */
    xSnakeMutex     = xSemaphoreCreateMutex();
    xLcdMutex       = xSemaphoreCreateMutex();
    xDirectionEvent = xEventGroupCreate();

    /* Initialize game state  */
    initGame();

    /* Create tasks */
    if (xTaskCreate(vTaskSnake, "Snake", 256, NULL, 2, NULL) != pdPASS ||
            xTaskCreate(vTaskInput, "Input", 128, NULL, 3, NULL) != pdPASS)
    {
        /* Task creation failed ¡ª display error message on screen */
        xSemaphoreTake(xLcdMutex, portMAX_DELAY);
        drawString(0, 0, "Task fail", Font_7x10, 0xFFFF, 0x0000);
        xSemaphoreGive(xLcdMutex);
        while (1) {}
    }

    /* Start the FreeRTOS scheduler ¡ª does not return */
    vTaskStartScheduler();

    while (1) {}
}
