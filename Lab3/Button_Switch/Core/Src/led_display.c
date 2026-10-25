#include "main.h"
#include "led_display.h"

int led_buffer[4] = {0, 0, 0, 0};

void display7SEG(int num) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);

    switch (num) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
            break;
    }
}

void update7SEG(int index) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13, GPIO_PIN_SET);

    display7SEG(led_buffer[index]);

    switch (index) {
        case 0: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); break;
        case 1: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); break;
        case 2: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); break;
        case 3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); break;
    }
}

void clearAllTrafficLights(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
}

void toggleRedTrafficLights(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_2 | GPIO_PIN_5, GPIO_PIN_RESET);
}

void toggleAmberTrafficLights(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_4);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_5, GPIO_PIN_RESET);
}

void toggleGreenTrafficLights(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_5);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_RESET);
}
