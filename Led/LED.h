/*
 * LED.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef LED_H_
#define LED_H_

typedef struct
{
	Dio_ChannelType Channel;
	Dio_LevelType Level;

}LED_t;
void LedOn(LED_t *LedPtrConfig);
void LedOff(LED_t *LedPtrConfig);
void LedToggle(LED_t *LedPtrConfig);

#endif /* LED_H_ */
