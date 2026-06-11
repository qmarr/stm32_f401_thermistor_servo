/*
 * control.h
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */

#ifndef CONTROL_H_
#define CONTROL_H_



#include <stdint.h>

typedef enum
{
    CONTROL_STATE_NORMAL = 0,
    CONTROL_STATE_OVERHEAT = 1
} ControlState_t;

typedef struct
{
    float temp_high;
    float temp_low;

    float servo_near_angle;
    float servo_away_angle;

    ControlState_t state;
    float servo_angle;
} ThresholdControl_t;

void ThresholdControl_Init(
    ThresholdControl_t *control,
    float temp_high,
    float temp_low,
    float servo_near_angle,
    float servo_away_angle
);

float ThresholdControl_Update(ThresholdControl_t *control, float temp_norm);

ControlState_t ThresholdControl_GetState(ThresholdControl_t *control);

#endif /* CONTROL_H_ */
