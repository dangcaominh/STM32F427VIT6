#ifndef __OV2640_H
#define __OV2640_H

#include <stdint.h>
#include "main.h"

/* Khai báo I2C phần cứng sử dụng */
extern I2C_HandleTypeDef hi2c1;

/* Địa chỉ I2C dạng 8-bit (HAL tự xử lý bit R/W) */
#define OV2640_DEVICE_ADDR      0x60
#define OV2640_DEVICE_ID        0x2642

/* REGISTER BANK SELECT */
#define OV2640_DSP_RA_DLMT      0xFF
#define OV2640_BANK_DSP         0x00
#define OV2640_BANK_SENSOR      0x01

/* SENSOR BANK REGISTERS (0x01) */
#define OV2640_SENSOR_PIDH      0x0A
#define OV2640_SENSOR_PIDL      0x0B
#define OV2640_SENSOR_COM7      0x12
#define OV2640_COM7_RESET       0x80

/* DSP BANK REGISTERS (0x00) */
#define OV2640_DSP_QS           0x44    // Chất lượng JPEG (0x00 = cao nhất, 0x3F = thấp nhất)
#define OV2640_DSP_IMAGE_MODE   0xDA

/* RESOLUTIONS */
typedef enum {
    OV2640_RES_160x120 = 0, // QQVGA
    OV2640_RES_320x240,     // QVGA
    OV2640_RES_640x480,     // VGA
    OV2640_RES_800x600,     // SVGA
    OV2640_RES_1600x1200    // UXGA
} ov2640_resolution_t;

/* FUNCTION PROTOTYPES */
uint8_t OV2640_WR_Reg(uint8_t reg, uint8_t value);
uint8_t OV2640_RD_Reg(uint8_t reg);

uint8_t OV2640_Init(void);
uint8_t OV2640_Init_JPEG(ov2640_resolution_t res);
uint16_t OV2640_ReadID(void);

uint8_t OV2640_Set_Resolution(ov2640_resolution_t res);
uint8_t OV2640_Set_JPEG_Quality(uint8_t quality);

#endif /* __OV2640_H */