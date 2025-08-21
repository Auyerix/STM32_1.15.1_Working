#ifndef INC_MODBUS_H_
#define INC_MODBUS_H_
#include "inttypes.h"

extern osMutexId coilMutexHandle;
extern osMutexId discreteMutexHandle;

// ---------COMMANDS------------------------------//
#define MB_FN_READ_COILS			(0x01)
#define MB_FN_READ_DISCRETE		(0x02)
#define MB_FN_READ_HOLDING		(0x03)
#define MB_FN_READ_INPUT			(0x04)
#define MB_FN_WRITE_S_COIL		(0x05)
#define MB_FN_WRITE_S_HOLDING	(0x06)
#define MB_FN_WRITE_M_COIL		(0x0F)
#define MB_FN_WRITE_M_HOLDING	(0x10)
//---------EXCEPTION CODES------------------------//
#define MB_EXCEPTION_OK							(0x00)
#define MB_EXCEPTION_FN_UNSUPPORTED (0x01)
#define MB_EXCEPTION_DATA_ADDR			(0x02)
#define MB_EXCEPTION_DATA_VAL				(0x03)
//---------MB TCP RELATED------------------------//
#define MB_MBAP_TRANSACTION_ID_H	(0)
#define MB_MBAP_TRANSACTION_ID_L	(1)
#define MB_MBAP_PROTOCOL_ID_H 		(2)
#define MB_MBAP_PROTOCOL_ID_L 		(3)
#define MB_MBAP_LEN_H 						(4)
#define MB_MBAP_LEN_L 						(5)
#define MB_MBAP_CLIENT_ID 				(6)
#define MB_MBAP_SIZE 							(7)
#define MB_TCP_PORT 							(502)
#define MB_MBAP_END								(MB_MBAP_CLIENT_ID)

#define MB_PDU_MAXSIZE (253)
// -------------------------- CONFIG START-------------------------------//
#define MB_ADU_MAXSIZE	(MB_PDU_MAXSIZE + MB_MBAP_SIZE)
#define MB_PDU_START		(MB_MBAP_END+1)

#define MB_COILS_ST			(0)
#define MB_COILS_Q			(0xFF)
#define MB_DISCRETE_ST	(MB_COILS_ST + MB_COILS_Q)
#define MB_DISCRETE_Q		(0xFF)
#define MB_HOLDING_ST 	(MB_DISCRETE_ST + MB_DISCRETE_Q)
#define MB_HOLDING_Q		(25)
#define MB_INPUT_ST			(MB_HOLDING_ST + MB_HOLDING_Q)
#define MB_INPUT_Q			(8)
#define MB_MEMORY_SIZE	(MB_COILS_Q + MB_DISCRETE_Q + MB_HOLDING_Q + MB_INPUT_Q)
// -------------------------- CONFIG END-------------------------------//

//---------BYTE POSITIONS IN PDU------------------------//
#define MB_PDU_FN									(MB_PDU_START)
#define MB_PDU_R_ST_ADDR_H				(MB_PDU_START + 1)
#define MB_PDU_R_ST_ADDR_L				(MB_PDU_START + 2)
#define MB_PDU_R_QUANTITY_H				(MB_PDU_START + 3)
#define MB_PDU_R_QUANTITY_L				(MB_PDU_START + 4)

#define MB_PDU_W_REG_ADDR_H				(MB_PDU_START + 1)
#define MB_PDU_W_REG_ADDR_L				(MB_PDU_START + 2)
#define MB_PDU_W_REG_VAL_H				(MB_PDU_START + 3)
#define MB_PDU_W_REG_VAL_L				(MB_PDU_START + 4)

#define MB_PDU_EXCEPTION_CODE			(MB_PDU_START + 1)
#define MB_PDU_REPL_N							(MB_PDU_START + 1)

// para definir el estado que Modbus le manda a las bobinas
#define MB_ON							(1)
#define MB_OFF							(0)

// to define which holding register map to the IP configuration

#define MB_IP_ADDRESS_0			(10)
#define MB_IP_ADDRESS_1 		(11)
#define MB_IP_ADDRESS_2 		(12)
#define MB_IP_ADDRESS_3 		(13)
#define MB_NETMASK_ADDRESS_0	(14)
#define MB_NETMASK_ADDRESS_1	(15)
#define MB_NETMASK_ADDRESS_2	(16)
#define MB_NETMASK_ADDRESS_3	(17)
#define MB_GATEWAY_ADDRESS_0	(18)
#define MB_GATEWAY_ADDRESS_1	(19)
#define MB_GATEWAY_ADDRESS_2	(20)
#define MB_GATEWAY_ADDRESS_3	(21)

// define Modbus Holding to use as a switch to save and restore from eeprom

#define MB_SWITH				(7)

// Server Status

#define MB_SERVER_STATUS		(24)



// process request and returns ADU size of reply
uint16_t mb_process(uint8_t *mb_repl_buf, uint8_t *mb_req_buf, uint16_t req_buf_len);


//Variables
extern uint8_t coil_status[MB_COILS_Q];
extern uint8_t discrete_status[MB_DISCRETE_Q];
extern uint16_t input_status[MB_INPUT_Q];
extern uint16_t holding_registers[MB_HOLDING_Q];


#endif /* INC_MODBUS_H_ */
