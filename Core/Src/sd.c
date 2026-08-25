#include "main.h"
#include "fatfs.h"

extern SD_HandleTypeDef hsd;

uint8_t BSP_SD_Init(void)
{
  uint8_t sd_state = MSD_OK;
  /* Check if the SD card is plugged in the slot */
  if (BSP_SD_IsDetected() != SD_PRESENT)
  {
    return MSD_ERROR;
  }
  /* HAL SD initialization */
  sd_state = HAL_SD_Init(&hsd);
  /* Configure SD Bus width (4 bits mode selected) */
  if (sd_state == MSD_OK)
  {
    /* Enable wide operation */
    MODIFY_REG(hsd.Instance->CLKCR, SDIO_CLKCR_WIDBUS_Msk | 0xFFU, SDIO_BUS_WIDE_1B | SDIO_INIT_CLK_DIV);
    if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK)
    {
      sd_state = MSD_ERROR;
    }
  }

  return sd_state;
}