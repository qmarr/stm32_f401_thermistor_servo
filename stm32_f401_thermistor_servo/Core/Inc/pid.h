/*
 * pid.h
 *
 *  Created on: Jun 11, 2026
 *      Author: komar
 */

#ifndef PID_H_
#define PID_H_

typedef struct
{
    float kp;
    float ki;
    float kd;

    float integral;
    float previous_error;

    float output_min;
    float output_max;

    float integral_min;
    float integral_max;
} PID_t;

void PID_Init(
    PID_t *pid,
    float kp,
    float ki,
    float kd,
    float output_min,
    float output_max,
    float integral_min,
    float integral_max
);

void PID_Reset(PID_t *pid);

float PID_Update(PID_t *pid, float error, float dt);


#endif /* PID_H_ */
