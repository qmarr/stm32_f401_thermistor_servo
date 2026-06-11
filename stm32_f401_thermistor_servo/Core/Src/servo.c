/*
 * servo.c
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */


#include "servo.h"

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


void Servo_Init(
    Servo_t *servo,
    TIM_HandleTypeDef *htim,
    uint32_t channel,
    float min_angle,
    float max_angle,
    float min_pulse_us,
    float max_pulse_us
)
{
    servo->htim = htim;
    servo->channel = channel;

    servo->min_angle = min_angle;
    servo->max_angle = max_angle;

    servo->min_pulse_us = min_pulse_us;
    servo->max_pulse_us = max_pulse_us;
}


void Servo_Start(Servo_t *servo)
{
    HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

void Servo_SetPulseUs(Servo_t *servo, float pulse_us)
{
    pulse_us = clamp_float(pulse_us, servo->min_pulse_us, servo->max_pulse_us);

    /*
     * Timer is configured as:
     * 1 timer tick = 1 us
     *
     * So CCR value equals pulse width in microseconds.
     */
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, (uint32_t)pulse_us);
}

void Servo_SetAngle(Servo_t *servo, float angle)
{
    angle = clamp_float(angle, servo->min_angle, servo->max_angle);

    float angle_range = servo->max_angle - servo->min_angle;
    float pulse_range = servo->max_pulse_us - servo->min_pulse_us;

    float normalized = (angle - servo->min_angle) / angle_range;
    float pulse_us = servo->min_pulse_us + normalized * pulse_range;

    Servo_SetPulseUs(servo, pulse_us);
}
