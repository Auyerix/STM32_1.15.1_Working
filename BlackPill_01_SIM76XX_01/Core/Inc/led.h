/*
 * led.h
 *
 *  Created on: Sep 3, 2025
 *      Author: gusta
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"  // ajustá según tu MCU

// Estados posibles del LED
typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_BLINK
} LED_State;

// Estructura de un LED
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    LED_State state;
} LED_Handle;

// ==== API ====

// Inicializa el manejador de LEDs
void LED_Init(LED_Handle *ledArray, int num);

// Cambia el estado de un LED
void LED_SetState(GPIO_TypeDef *port, uint16_t pin, LED_State state);

// Debe llamarse desde el callback del timer
void LED_UpdateBlink(void);

#endif /* INC_LED_H_ */
