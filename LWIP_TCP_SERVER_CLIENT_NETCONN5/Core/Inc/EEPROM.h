/**
  ******************************************************************************

  EEPROM.h Using the HAL I2C Functions
  Author:   ControllersTech
  Updated:  Feb 16, 2021

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"


//HAL_StatusTypeDef EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
HAL_StatusTypeDef EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
//void EEPROM_PageErase (uint16_t page);

/**
 * @brief This function detect transition between 0 and 1 or 2
 * 0 -> 1 Save the data on the registers to the first 12 positions in EEPROM
 * 0 -> 2 Read the data from the EEPROM to the registers
 * Hoding register to be used are defined in Modbus.h
 * @param void
 * @param void
 * @return void
 */
void detectTransitions(void);


#endif /* INC_EEPROM_H_ */
