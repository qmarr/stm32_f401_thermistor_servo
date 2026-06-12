/*
 * pid.c
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */


#include "pid.h"

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

void PID_Init(
    PID_t *pid,
    float kp,
    float ki,
    float kd,
    float output_min,
    float output_max,
    float integral_min,
    float integral_max
)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0f;
    pid->previous_error = 0.0f;

    pid->output_min = output_min;
    pid->output_max = output_max;

    pid->integral_min = integral_min;
    pid->integral_max = integral_max;
}

void PID_Reset(PID_t *pid)
{
    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
}

float PID_Update(PID_t *pid, float error, float dt)
{
    pid->integral += error * dt;
    pid->integral = clamp_float(pid->integral, pid->integral_min, pid->integral_max);

    float derivative = (error - pid->previous_error) / dt;

    float output =
        pid->kp * error +
        pid->ki * pid->integral +
        pid->kd * derivative;

    output = clamp_float(output, pid->output_min, pid->output_max);

    pid->previous_error = error;

    return output;
}
