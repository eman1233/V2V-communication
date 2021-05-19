/*
 * Switch.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef SWITCH_H_
#define SWITCH_H_



typedef struct
{
	Dio_ChannelType Channel;
	Dio_LevelType Level;
}Switch_t;


Std_ReturnType SwitchStatus(Switch_t *SwtichPtrConfig);

#endif /* SWITCH_H_ */
