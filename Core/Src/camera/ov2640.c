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
        return;
    }

    // Khởi tạo camera trực tiếp sang chế độ JPEG, độ phân giải 320x240 (QVGA)
    OV2640_Init_JPEG(OV2640_RES_320x240);

    // Tùy chỉnh chất lượng nén JPEG nếu cần (0x08 = nét cao, 0x1C = nét vừa)
    OV2640_Set_JPEG_Quality(0x0C);
}