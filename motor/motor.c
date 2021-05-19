/*
 * motor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#include "motor.h"
#include "E:\1\NTI\AVR\AVR\RTOS\MCAL\GPIO\Dio.h"

void MotorDirectionClockWise(Motor_t *MotorPtrConfig)
{

	Dio_WriteChannel(MotorPtrConfig->Channel2,!(MotorPtrConfig->Level));
	Dio_WriteChannel(MotorPtrConfig->Channel1,MotorPtrConfig->Level);

}
void MotorDirectionAntiClockWise(Motor_t *MotorPtrConfig)
{
	Dio_WriteChannel(MotorPtrConfig->Channel1,!(MotorPtrConfig->Level));
	Dio_WriteChannel(MotorPtrConfig->Channel2,MotorPtrConfig->Level);
}

void MotorOff(Motor_t *MotorPtrConfig)
{
	Dio_WriteChannel(MotorPtrConfig->Channel1,!(MotorPtrConfig->Level));
	Dio_WriteChannel(MotorPtrConfig->Channel2,!(MotorPtrConfig->Level));
}
