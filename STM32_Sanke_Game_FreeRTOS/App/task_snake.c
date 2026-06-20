#include "task_snake.h"
#include "game_logic.h"
#include "display.h"
#include "main.h"

void vTaskSnake(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {
        EventBits_t bits = xEventGroupWaitBits(
                               xDirectionEvent,
                               DIR_EVENT_UP | DIR_EVENT_DOWN | DIR_EVENT_LEFT | DIR_EVENT_RIGHT,
                               pdTRUE, pdFALSE,
                               pdMS_TO_TICKS(80));

        xSemaphoreTake(xSnakeMutex, portMAX_DELAY);

        if ((bits & DIR_EVENT_UP)    && snake.dir != DIR_DOWN)  snake.dir = DIR_UP;
        if ((bits & DIR_EVENT_DOWN)  && snake.dir != DIR_UP)    snake.dir = DIR_DOWN;
        if ((bits & DIR_EVENT_LEFT)  && snake.dir != DIR_RIGHT) snake.dir = DIR_LEFT;
        if ((bits & DIR_EVENT_RIGHT) && snake.dir != DIR_LEFT)  snake.dir = DIR_RIGHT;

        moveSnake();
        checkCollision();
        drawHead(snake.body[0]);

        xSemaphoreGive(xSnakeMutex);
    }
}
