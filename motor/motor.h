/*
 * motor.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Dio.h"
typedef struct
{
	Dio_ChannelType Channel1;
	Dio_ChannelType Channel2;
	Dio_LevelType Level;
}Motor_t;

void MotorOn(Motor_t *MotorPtrConfig);
void MotorOff(Motor_t *MotorPtrConfig);
void MotorDirectionClockWise(Motor_t *MotorPtrConfig);
void MotorDirectionAntiClockWise(Motor_t *MotorPtrConfig);

#endif /* MOTOR_H_ */
