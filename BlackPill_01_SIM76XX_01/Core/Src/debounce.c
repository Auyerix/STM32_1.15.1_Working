/*
 * debounce.c
 *
 *  Created on: Sep 2, 2025
 *      Author: gusta
 */

#include "debounce.h"
#include "gpio.h"
#include "stm32f4xx_hal.h" // o el header del HAL que uses


bool Pulsador_Presionado(void) {
    static uint32_t lastPressTime = 0;
    static bool lastState = GPIO_PIN_SET; // con pull-up, botón no presionado = HIGH

    bool currentState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    uint32_t now = HAL_GetTick();

    // Detecta flanco descendente
    if (lastState == GPIO_PIN_SET && currentState == GPIO_PIN_RESET) {
        // Comprueba debounce
        if ((now - lastPressTime) > 50) { // 50 ms debounce
            lastPressTime = now;
            lastState = currentState;
            return true; // pulso detectado
        }
    }

    lastState = currentState;
    return false;
}
