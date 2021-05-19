/*
 * Switch.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */


#include "E:\1\NTI\AVR\AVR\RTOS\MCAL\GPIO\Dio.h"
#include "Switch.h"

#include "Switch_Cfg.h"
#include "Std_Types.h"

#if(Mode==Pullup)
Std_ReturnType SwitchStatus(Switch_t *SwtichPtrConfig)
{
	Std_ReturnType Return;
	SwtichPtrConfig->Level=Dio_ReadChannel(SwtichPtrConfig->Channel);
	if(SwtichPtrConfig->Level)
	{
		Return = E_NOT_OK;
	}
	else
	{
		Return = E_OK;
	}

	return Return;
}
#elif(Mode==PullDown)
Std_ReturnType SwitchStatus(Switch_t *SwtichPtrConfig)
{
	Std_ReturnType Return;
	SwtichPtrConfig->Level=Dio_ReadChannel(SwtichPtrConfig->Channel);
	Return=SwtichPtrConfig->Level;
	if(SwtichPtrConfig->Level)
	{
		Return = E_OK;
	}
	else
	{
		Return = E_NOT_OK;
	}
	return Return;
}
#endif
