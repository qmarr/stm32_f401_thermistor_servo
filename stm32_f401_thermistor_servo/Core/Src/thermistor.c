/*
 * thermistor.c
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */

#include "thermistor.h"

#define THERMISTOR_ADC_MAX_VALUE 4095.0f

static float clamp_float(float value, float min_value, float max_value)
{
    if (value < min_value)
    {
        return min_value;
    }

    if (value > max_value)
    {
        return max_value;
    }

    return value;
}

void Thermistor_Init(Thermistor_t *thermistor, float initial_adc, float alpha)
{
    thermistor->adc_filtered = initial_adc;
    thermistor->alpha = alpha;
}

uint32_t Thermistor_ReadAdcRaw(ADC_HandleTypeDef *hadc) {
	uint32_t adc_value = 0;
	HAL_ADC_Start(hadc);

	if(HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY) == HAL_OK) {
		adc_value = HAL_ADC_GetValue(hadc);
	}

	HAL_ADC_Stop(hadc);

	return adc_value;
}

float Thermistor_UpdateFilter(Thermistor_t *thermistor, uint32_t adc_raw) {
	thermistor->adc_filtered = thermistor->adc_filtered +
							   thermistor->alpha * ((float)adc_raw - thermistor->adc_filtered);
	return thermistor->adc_filtered;
}

float Thermistor_GetTempNorm(float adc_filtered) {
	float temp_norm = 1.0f - (adc_filtered / THERMISTOR_ADC_MAX_VALUE);
	return clamp_float(temp_norm, 0.0f, 1.0f);
}
