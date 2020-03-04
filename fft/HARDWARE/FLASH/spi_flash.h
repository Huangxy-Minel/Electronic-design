#ifndef _SPI_FLASH_H
#define _SPI_FLASH_H

#include "sys.h"

#define SPI2_GPIO GPIOB
#define SPI2_CS_Pin GPIO_Pin_12
#define SPI2_SCK_Pin GPIO_Pin_13
#define SPI2_MISO_Pin GPIO_Pin_14
#define SPI2_MOSI_Pin GPIO_Pin_15

#define SPI2_SCK_PinSource  GPIO_PinSource13
#define SPI2_MISO_PinSource  GPIO_PinSource14
#define SPI2_MOSI_PinSource  GPIO_PinSource15

#define SPI2_CS PBout(12)
#define SPI2_SCK PBout(13)
#define SPI2_MOSI PBout(14)
#define SPI2_MISO PBout(15)

u8 SPI2_ReadWriteByte(u8 TxData);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
void spi2_init(void);

#endif
