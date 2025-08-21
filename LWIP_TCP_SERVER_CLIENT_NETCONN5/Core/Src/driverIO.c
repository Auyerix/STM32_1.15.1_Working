/*
 * driverIO.c
 *
 *  Created on: Dec 11, 2024
 *      Author: gusta
 */

#include "main.h"
#include "cmsis_os.h"
#include <string.h>  // Para memcpy
#include "driverIO.h"
//#include "Modbus.h"  (ya está en driverIO.h)
#include "EEPROM.h"


/*Variables privadas para este driver donde se alojan entradas y salidas físicas*/
// Estado de los coils en hardware
static uint8_t out_coil_status[MB_COILS_Q];
// Estado de las entradas discretas en hardware
static uint8_t in_discrete_status[MB_DISCRETE_Q];



void inputOutputControl(void){

	//in_discrete_status[0] = 1 ;

	ReadGPIO();

	osMutexWait(discreteMutexHandle, osWaitForever);

	memcpy(discrete_status, in_discrete_status, HD_DISCRETE_Q * sizeof(uint8_t));

	osMutexRelease(discreteMutexHandle);

	osMutexWait(coilMutexHandle, osWaitForever);

	memcpy(out_coil_status, coil_status, HD_COILS_Q * sizeof(uint8_t));

	osMutexRelease(coilMutexHandle);


	WriteGPIO();

}

//LED ROJO para ser usado cuando el remoto esté en running
void TurnOnRedLED(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // Encender el LED rojo
    //HAL_GPIO_WritePin(output_01_GPIO_Port, output_01_Pin, GPIO_PIN_SET);
}

void TurnOffRedLED(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); // apagar el LED rojo
    //HAL_GPIO_WritePin(output_01_GPIO_Port, output_01_Pin, GPIO_PIN_RESET);
}

void ReadGPIO(void){

	//llave no presionada input en 1 por pull up vía software
	if(READ_INPUT_01()){
		HD_INPUT01 = HD_OFF;
	}
	else{
		HD_INPUT01 = HD_ON;
	}

	if(READ_INPUT_02()){
		HD_INPUT02 = HD_OFF;
	}
	else{
		HD_INPUT02 = HD_ON;
	}

	if(READ_INPUT_03()){
		HD_INPUT03 = HD_OFF;
	}
	else{
		HD_INPUT03 = HD_ON;
	}

	if(READ_INPUT_04()){
		HD_INPUT04 = HD_OFF;
	}
	else{
		HD_INPUT04 = HD_ON;
	}



}

void WriteGPIO(void){

	if (HD_OUTPUT01 == MB_ON){
		SET_OUTPUT_01(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_01(GPIO_PIN_RESET);
	}
	if (HD_OUTPUT02 == MB_ON){
		SET_OUTPUT_02(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_02(GPIO_PIN_RESET);
	}
	if (HD_OUTPUT03 == MB_ON){
		SET_OUTPUT_03(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_03(GPIO_PIN_RESET);
	}
	if (HD_OUTPUT04 == MB_ON){
		SET_OUTPUT_04(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_04(GPIO_PIN_RESET);
	}
/*------------------Auxiliar Outputs --------------------------*/

	// Client connected
	if (holding_registers[MB_SERVER_STATUS] == MB_ON){
		SET_OUTPUT_STATUS(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_STATUS(GPIO_PIN_RESET);
	}

	//Auxiliar LED AZUL
	if (HD_OUTPUT_LED_BLUE == MB_ON){
		SET_OUTPUT_LED_BLUE(GPIO_PIN_SET);
	}
	else{
		SET_OUTPUT_LED_BLUE(GPIO_PIN_RESET);
	}

}
