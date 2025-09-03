/*
 * led.c
 *
 *  Created on: Sep 3, 2025
 *      Author: gusta
 */

#include "led.h"

// Puntero global al array de LEDs y cantidad
static LED_Handle *leds = NULL;
static int ledCount = 0;

// Inicialización
void LED_Init(LED_Handle *ledArray, int num) {
    leds = ledArray;
    ledCount = num;
}

// Cambiar estado de un LED
void LED_SetState(GPIO_TypeDef *port, uint16_t pin, LED_State state) {
    if (!leds) return; // seguridad

    for (int i = 0; i < ledCount; i++) {
        if (leds[i].port == port && leds[i].pin == pin) {
            leds[i].state = state;

            if (state == LED_ON) {
                HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
            } else if (state == LED_OFF) {
                HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
            }
            // si es BLINK, el toggle se maneja en el timer
            break;
        }
    }
}

// Actualiza los LEDs en modo BLINK
void LED_UpdateBlink(void) {
    if (!leds) return;

    for (int i = 0; i < ledCount; i++) {
        if (leds[i].state == LED_BLINK) {
            HAL_GPIO_TogglePin(leds[i].port, leds[i].pin);
        }
    }
}

