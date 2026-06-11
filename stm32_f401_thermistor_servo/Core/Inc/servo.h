/*
 * servo.h
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "stm32f4xx_hal.h"

typedef struct
{
    TIM_HandleTypeDef *htim;
    uint32_t channel;

    float min_angle;
    float max_angle;

    float min_pulse_us;
    float max_pulse_us;
} Servo_t;

void Servo_Init(
    Servo_t *servo,
    TIM_HandleTypeDef *htim,
    uint32_t channel,
    float min_angle,
    float max_angle,
    float min_pulse_us,
    float max_pulse_us
);



void Servo_Start(Servo_t *servo);

void Servo_SetPulseUs(Servo_t *servo, float pulse_us);

void Servo_SetAngle(Servo_t *servo, float angle);


#endif /* SERVO_H_ */
