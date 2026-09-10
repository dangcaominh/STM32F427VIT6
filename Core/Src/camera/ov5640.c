#include "main.h"
#include "ov5640.h"

void Camera_Init_OV5640()
{
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, 1);
    while (OV5640_Init())
    {
        
    }
    OV5640_Light_Mode(0);		// set auto
    OV5640_Color_Saturation(3); // default
    OV5640_Exposure(4);		// +1 exposure compensation
    OV5640_Brightness(5);		// +1 brightness compensation
    OV5640_Contrast(3);			// default
    OV5640_Sharpness(33);		// set auto
    OV5640_RGB565_Mode();
    OV5640_OutSize_Set(0, 4, 320, 240); // set output size
}