/*
 * mqtt_functions.h
 *
 *  Created on: Sep 1, 2025
 *      Author: gusta
 */

#ifndef INC_MQTT_FUNCTIONS_H_
#define INC_MQTT_FUNCTIONS_H_

#include <stdbool.h>
#include <stdint.h>

extern uint8_t step;   // declaración externa

#define MAX_AT_CMD_LEN 128
#define APN "gprs.claro.com.ar"       // Tu APN
#define MQTT_CLIENT "cli01"



bool SIMTransmit_OLD(char *cmd, char* expected, uint32_t timeout_ms);
bool SIMTransmit(char *cmd, char* expected, uint32_t timeout_ms);
bool SIM_WaitForNetwork_Funcionaba(uint32_t timeout_ms);
bool SIM_WaitForNetwork(uint32_t timeout_ms);
bool MQTT_Init(void);
bool MQTT_Publish(const char* topic, const char* payload);
bool MQTT_ConnectToBroker(void);
void MQTT_Disconnect(void);
void MQTT_Reset(void);



#endif /* INC_MQTT_FUNCTIONS_H_ */
