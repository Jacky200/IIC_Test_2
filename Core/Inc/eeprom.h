#ifndef _EEPROM_H
#define _EEPROM_H

#include"stm32f1xx_hal.h"


#define EEPROM_DEV_ADDR     (0xA0)
#define EEPROM_WR           (0x00)
#define EEPROM_RD           (0x01)

#define EEPROM_WORD_ADDR_SIZE (0x08)

void EEPROM_WirteByte(uint16_t addr,uint8_t data);
void EEPROM_ReadByte(uint16_t addr,uint8_t *pdata);
void EEPROM_WriteNByte(uint16_t addr,uint8_t *pdata,uint16_t size);
void EEPROM_ReadNByte(uint16_t addr,uint8_t *pdata,uint16_t size);
#endif
