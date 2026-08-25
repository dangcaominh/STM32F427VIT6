#include "main.h"
#include "ili9341.h"


extern TIM_HandleTypeDef htim2;

void LCD_Init()
{
    HAL_GPIO_WritePin(LCD_NRST_GPIO_Port, LCD_NRST_Pin, GPIO_PIN_RESET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(LCD_NRST_GPIO_Port, LCD_NRST_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    lcdInit();
    lcdTest();
    HAL_Delay(1000);
    lcdSetOrientation(LCD_ORIENTATION_LANDSCAPE);
    lcdFillRGB(COLOR_BLACK);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    htim2.Instance->CCR3 = 100;
}