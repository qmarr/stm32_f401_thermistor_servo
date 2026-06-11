/*
 * thermistor.h
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */

#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct
{
    float adc_filtered;
    float alpha;
} Thermistor_t;

void Thermistor_Init(Thermistor_t *thermistor, float initial_adc, float alpha);

uint32_t Thermistor_ReadAdcRaw(ADC_HandleTypeDef *hadc);

float Thermistor_UpdateFilter(Thermistor_t *thermistor, uint32_t adc_raw);

float Thermistor_GetTempNorm(float adc_filtered);


#endif /* THERMISTOR_H_ */
