/*
 * control.c
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */
#include "control.h"

void ThresholdControl_Init(
    ThresholdControl_t *control,
    float temp_high,
    float temp_low,
    float servo_near_angle,
    float servo_away_angle
)
{
    control->temp_high = temp_high;
    control->temp_low = temp_low;

    control->servo_near_angle = servo_near_angle;
    control->servo_away_angle = servo_away_angle;

    control->state = CONTROL_STATE_NORMAL;
    control->servo_angle = servo_near_angle;
}

float ThresholdControl_Update(ThresholdControl_t *control, float temp_norm)
{
    if (temp_norm > control->temp_high)
    {
        control->state = CONTROL_STATE_OVERHEAT;
        control->servo_angle = control->servo_away_angle;
    }
    else if (temp_norm < control->temp_low)
    {
        control->state = CONTROL_STATE_NORMAL;
        control->servo_angle = control->servo_near_angle;
    }

    return control->servo_angle;
}

ControlState_t ThresholdControl_GetState(ThresholdControl_t *control)
{
    return control->state;
}

