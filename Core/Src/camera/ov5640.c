#include "main.h"
#include "ov5640.h"

void Camera_Init()
{
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, 1);
    while (OV5640_Init())
    {
        
    }
    OV5640_Light_Mode(0);		// set auto
    OV5640_Color_Saturation(3); // default
    OV5640_Brightness(4);		// default
    OV5640_Contrast(3);			// default
    OV5640_Sharpness(33);		// set auto
    OV5640_JPEG_Mode();
    OV5640_OutSize_Set(0, 4, 320, 240); // set output size
}