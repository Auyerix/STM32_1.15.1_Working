/*
 * PWM.h
 *
 *  Created on: Jan 29, 2026
 *      Author: gusta
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "main.h"      // Contiene las definiciones de las instancias como htim1

/* Función para cambiar frecuencia y duty sobre la marcha */
void Ajustar_PWM(uint16_t periodo_ms, float duty_porcentaje);





#endif /* INC_PWM_H_ */
