/*
 * LED.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */


#include "E:\1\NTI\AVR\AVR\RTOS\MCAL\GPIO\Dio.h"
#include "LED_Cfg.h"
#include "LED.h"

#if(MODE==ActiveHigh)
void LedOn(LED_t *LedPtrConfig)
{
	LedPtrConfig->Level=STD_HIGH;
	Dio_WriteChannel(LedPtrConfig->Channel,LedPtrConfig->Level);
}
void LedOff(LED_t *LedPtrConfig)
{
	LedPtrConfig->Level=STD_LOW;
	Dio_WriteChannel(LedPtrConfig->Channel,LedPtrConfig->Level);

}
#elif(MODE==ActiveLow)
void LedOn(LED_t *LedPtrConfig)
{
	LedPtrConfig->Level=STD_LOW;
	Dio_WriteChannel(LedPtrConfig->Channel,LedPtrConfig->Level);
}
void LedOff(LED_t *LedPtrConfig)
{
	LedPtrConfig->Level=STD_HIGH;
	Dio_WriteChannel(LedPtrConfig->Channel,LedPtrConfig->Level);

}
#endif

void LedToggle(LED_t *LedPtrConfig)
{
	//LedPtrConfig->Level=STD_HIGH;
	LedPtrConfig->Level=Dio_FlipChannel(LedPtrConfig->Channel);
}
