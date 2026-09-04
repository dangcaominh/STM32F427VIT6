#include <stdio.h>
#include "main.h"
#include "ov2640.h"

void Camera_Init_OV2640(void)
{
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    
    uint16_t sensor_id = OV2640_ReadID();
    if (sensor_id != OV2640_DEVICE_ID)
    {
        // Lỗi: Không tìm thấy camera OV2640
        printf("Cannot find OV2640");
        return;
    }

    OV2640_Init();

}