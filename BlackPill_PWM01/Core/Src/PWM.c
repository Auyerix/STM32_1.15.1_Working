/*
 * PWM.c
 *
 *  Created on: Jan 29, 2026
 *      Author: gusta
 */

#include "PWM.h"

// Esto le dice al compilador: "Busca la variable htim1 en otro archivo (main.c)"
extern TIM_HandleTypeDef htim3;

/**
 * @brief Actualiza PWM con rango extendido
 * @param periodo_ms: De 1 a 6553 (Límite de 16 bits con PSC 8399)
 * @param duty_porcentaje: De 0.0 a 100.0
 */
void Ajustar_PWM(uint16_t periodo_ms, float duty_porcentaje) {

    // 1. Protección de límites (Hard Limits)
    // El mínimo es 1ms (ARR=9). El máximo es 6553ms (ARR=65529).
    if (periodo_ms < 1)    periodo_ms = 1;
    if (periodo_ms > 6553) periodo_ms = 6553;

    if (duty_porcentaje > 100.0f) duty_porcentaje = 100.0f;
    if (duty_porcentaje < 0.0f)   duty_porcentaje = 0.0f;

    // 2. Calcular ARR
    // Cada ms son 10 ticks (0.1ms por tick)
    uint32_t nuevo_arr = (periodo_ms * 10) - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim3, nuevo_arr);

    // 3. Calcular CCR (Pulse)
    // Usamos (nuevo_arr + 1) para que el cálculo sea exacto sobre el periodo total
    uint32_t nuevo_pulse = (uint32_t)((duty_porcentaje / 100.0f) * (nuevo_arr + 1));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, nuevo_pulse);
}
