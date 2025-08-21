
/**
  ******************************************************************************

  EEPROM.c Using the HAL I2C Functions
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

#include "main.h"  // para tener SendString
#include "EEPROM.h"
//#include "math.h"
#include "string.h"
#include "cmsis_os.h"
#include "Modbus.h"

// Define the I2C
extern I2C_HandleTypeDef hi2c2;
#define EEPROM_I2C &hi2c2

// EEPROM ADDRESS (8bits)
#define EEPROM_ADDR 0xA0

// Define the Page Size and number of pages
#define PAGE_SIZE 64     // in Bytes
#define PAGE_NUM  512    // number of pages

/* Agregado por GA para evitar cuenta*/
#define PAGE_BIT       5  // number of bits to map PAGE_SIZE (depend on the EEPROM size)

//Vector de holdings
//extern uint16_t holding_registers[MB_HOLDING_Q]; //porque la trae el include Modbus.h

uint8_t IP_To_Eeprom[12]; // = {192,168,1,135,255,255,255,0,192,168,1,1};
uint8_t IP_From_Eeprom[12];
/*****************************************************************************************************************************************/
uint8_t bytes_temp[4];

// function to determine the remaining bytes
static uint16_t bytestowrite (uint16_t size, uint16_t offset)
{
	if ((size+offset)<PAGE_SIZE) return size;
	else return PAGE_SIZE-offset;
}

/* write the data to the EEPROM
 * @page is the number of the start page. Range from 0 to PAGE_NUM-1
 * @offset is the start byte offset in the page. Range from 0 to PAGE_SIZE-1
 * @data is the pointer to the data to write in bytes
 * @size is the size of the data
 */
static HAL_StatusTypeDef EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{

	// Find out the number of bit, where the page addressing starts
	int paddrposition = PAGE_BIT; // Directamente el valor predefinido

	// calculate the start page and the end page
	uint16_t startPage = page;
	uint16_t endPage = page + ((size+offset)/PAGE_SIZE);

	// number of pages to be written
	uint16_t numofpages = (endPage-startPage) + 1;
	uint16_t pos=0;

	// write the data
	for (int i=0; i<numofpages; i++)
	{
		/* calculate the address of the memory location
		 * Here we add the page address with the byte address
		 */
		uint16_t MemAddress = startPage<<paddrposition | offset;
		uint16_t bytesremaining = bytestowrite(size, offset);  // calculate the remaining bytes to be written

		HAL_StatusTypeDef status = HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddress, 2, &data[pos], bytesremaining, 1000);  // write the data to the EEPROM

		// Check for errors in the write operation
		if (status != HAL_OK) {
			return status;  // Return the error status immediately
		}
		startPage += 1;  // increment the page, so that a new page address can be selected for further write
		offset=0;   // since we will be writing to a new page, so offset will be 0
		size = size-bytesremaining;  // reduce the size of the bytes
		pos += bytesremaining;  // update the position for the data buffer

		osDelay (5);  // Write cycle delay (5ms) OS Block state
	}

    return HAL_OK;  // If everything succeeds, return HAL_OK
}



/* READ the data from the EEPROM
 * @page is the number of the start page. Range from 0 to PAGE_NUM-1
 * @offset is the start byte offset in the page. Range from 0 to PAGE_SIZE-1
 * @data is the pointer to the data to write in bytes
 * @size is the size of the data
 */
HAL_StatusTypeDef EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int paddrposition = PAGE_BIT; // Directamente el valor predefinido

	uint16_t startPage = page;
	uint16_t endPage = page + ((size+offset)/PAGE_SIZE);

	uint16_t numofpages = (endPage-startPage) + 1;
	uint16_t pos=0;

	for (int i=0; i<numofpages; i++)
	{
		uint16_t MemAddress = startPage<<paddrposition | offset;
		uint16_t bytesremaining = bytestowrite(size, offset);
		HAL_StatusTypeDef status = HAL_I2C_Mem_Read(EEPROM_I2C, EEPROM_ADDR, MemAddress, 2, &data[pos], bytesremaining, 1000);
		// Check for errors in the read operation
		if (status != HAL_OK) {
			return status;  // Return the error status immediately
		}
		startPage += 1;
		offset=0;
		size = size-bytesremaining;
		pos += bytesremaining;
	}
    return HAL_OK;  // If everything succeeds, return HAL_OK
}

/* Erase a page in the EEPROM Memory
 * @page is the number of page to erase
 * In order to erase multiple pages, just use this function in the for loop
 */
static void EEPROM_PageErase (uint16_t page)
{
	// calculate the memory address based on the page number
	int paddrposition = PAGE_BIT; // Directamente el valor predefinido
	uint16_t MemAddress = page<<paddrposition;

	// create a buffer to store the reset values
	uint8_t data[PAGE_SIZE];
	memset(data,0xff,PAGE_SIZE);

	// write the data to the EEPROM
	HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddress, 2, data, PAGE_SIZE, 1000);

	osDelay (5);  // write cycle delay 
}

// Function to detect specific transitions
void detectTransitions() {
    static int previous_state = 0; // Variable to store the previous state

    if (previous_state == 0 && holding_registers[MB_SWITH] == 1) {
    	SendString("transition 0 - 1 SAVE TO EEPROM \r"); // 0-to-1 transition
    	IP_To_Eeprom[0] = holding_registers[MB_IP_ADDRESS_0];
    	IP_To_Eeprom[1] = holding_registers[MB_IP_ADDRESS_1];
    	IP_To_Eeprom[2] = holding_registers[MB_IP_ADDRESS_2];
    	IP_To_Eeprom[3] = holding_registers[MB_IP_ADDRESS_3];
    	IP_To_Eeprom[4] = holding_registers[MB_NETMASK_ADDRESS_0];
    	IP_To_Eeprom[5] = holding_registers[MB_NETMASK_ADDRESS_1];
    	IP_To_Eeprom[6] = holding_registers[MB_NETMASK_ADDRESS_2];
    	IP_To_Eeprom[7] = holding_registers[MB_NETMASK_ADDRESS_3];
    	IP_To_Eeprom[8] = holding_registers[MB_GATEWAY_ADDRESS_0];
    	IP_To_Eeprom[9] = holding_registers[MB_GATEWAY_ADDRESS_1];
    	IP_To_Eeprom[10] = holding_registers[MB_GATEWAY_ADDRESS_2];
    	IP_To_Eeprom[11] = holding_registers[MB_GATEWAY_ADDRESS_3];


    	if (EEPROM_Write(1,0,IP_To_Eeprom,12) != HAL_OK){
    		SendString("Read error EEPROM \r");
    	}
    } else if (previous_state == 0 && holding_registers[MB_SWITH] == 2) {
    	SendString("transition 0 - 2 READ from EEPROM \r"); // 0-to-2 transition
    	if (EEPROM_Read(1,0,IP_From_Eeprom,12) != HAL_OK){
    		SendString("Read error EEPROM \r");
    	}
    	else{
    		holding_registers[MB_IP_ADDRESS_0] =IP_From_Eeprom[0];
    		holding_registers[MB_IP_ADDRESS_1] =IP_From_Eeprom[1];
    		holding_registers[MB_IP_ADDRESS_2] =IP_From_Eeprom[2];
    		holding_registers[MB_IP_ADDRESS_3] =IP_From_Eeprom[3];
    		holding_registers[MB_NETMASK_ADDRESS_0] =IP_From_Eeprom[4];
    		holding_registers[MB_NETMASK_ADDRESS_1] =IP_From_Eeprom[5];
    		holding_registers[MB_NETMASK_ADDRESS_2] =IP_From_Eeprom[6];
    		holding_registers[MB_NETMASK_ADDRESS_3] =IP_From_Eeprom[7];
    		holding_registers[MB_GATEWAY_ADDRESS_0] =IP_From_Eeprom[8];
    		holding_registers[MB_GATEWAY_ADDRESS_1] =IP_From_Eeprom[9];
    		holding_registers[MB_GATEWAY_ADDRESS_2] =IP_From_Eeprom[10];
    		holding_registers[MB_GATEWAY_ADDRESS_3] =IP_From_Eeprom[11];
    	}
    }

    // Update the previous state
    previous_state = holding_registers[MB_SWITH];
}
