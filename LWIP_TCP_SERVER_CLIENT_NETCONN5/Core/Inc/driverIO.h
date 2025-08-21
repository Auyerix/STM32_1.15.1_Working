/*
 * driverIO.h
 *
 *  Created on: Dec 11, 2024
 *      Author: gusta
 */

#ifndef INC_DRIVERIO_H_
#define INC_DRIVERIO_H_

#include "modbus.h"  //para poder usar el tamaño de los vectores con los defines de modbus.h
					// y no volver a definir las variables como externas

/*-------------------Definiciones de hardware-----------------------------*/
//cantidad de bobinas físicas
#define HD_COILS_Q			(20)
//cantidad de entradas físicas
#define HD_DISCRETE_Q		(4)


/*-------------------Mapping status vector with HD variables-----------------------------*/
#define HD_OUTPUT01	out_coil_status[0]
#define HD_OUTPUT02	out_coil_status[1]
#define HD_OUTPUT03	out_coil_status[2]
#define HD_OUTPUT04	out_coil_status[3]

//#define HD_OUTPUT_STATUS	out_coil_status[10]
#define HD_OUTPUT_LED_BLUE	out_coil_status[11]


#define HD_INPUT01			in_discrete_status[0]
#define HD_INPUT02			in_discrete_status[1]
#define HD_INPUT03			in_discrete_status[2]
#define HD_INPUT04			in_discrete_status[3]

/*-------------------Mapping between Modbus and HAL -----------------------------*/
#define SET_OUTPUT_01(state) HAL_GPIO_WritePin(output_01_GPIO_Port, output_01_Pin, state);
#define SET_OUTPUT_02(state) HAL_GPIO_WritePin(output_02_GPIO_Port, output_02_Pin, state);
#define SET_OUTPUT_03(state) HAL_GPIO_WritePin(output_03_GPIO_Port, output_03_Pin, state);
#define SET_OUTPUT_04(state) HAL_GPIO_WritePin(output_04_GPIO_Port, output_04_Pin, state);

#define SET_OUTPUT_STATUS(state) HAL_GPIO_WritePin(output_status_GPIO_Port, output_status_Pin, state);
#define SET_OUTPUT_LED_BLUE(state) HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, state);

#define READ_INPUT_01() HAL_GPIO_ReadPin(input_01_GPIO_Port, input_01_Pin)
#define READ_INPUT_02() HAL_GPIO_ReadPin(input_02_GPIO_Port, input_02_Pin)
#define READ_INPUT_03() HAL_GPIO_ReadPin(input_03_GPIO_Port, input_03_Pin)
#define READ_INPUT_04() HAL_GPIO_ReadPin(input_04_GPIO_Port, input_04_Pin)

// Definición del estado de los discrete leidos en hardware
#define HD_ON							(1)
#define HD_OFF							(0)



extern osMutexId coilMutexHandle;
extern osMutexId discreteMutexHandle;

//Functions
void inputOutputControl(void);
void TurnOnRedLED(void);
void TurnOffRedLED(void);
void ReadGPIO(void);
void WriteGPIO(void);


//Variables
//extern uint8_t coil_status[MB_COILS_Q];
//extern uint8_t discrete_status[256];
//extern uint16_t input_status[10];
//extern uint16_t holding_registers[10];


#endif /* INC_DRIVERIO_H_ */
