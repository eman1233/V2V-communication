/*********************************************************

     * Name              : Eman Megahed
	 * Data              : 6/1/2021
	 * Version           : 1.0
	 * SWC               : DIO

**********************************************************/

#include "Dio.h"
#include "Dio_MemMap.h"
#include "Det.h"
#include "SchM_Dio.h"

extern const Dio_ChannelStatus  ChannelStatus [TOTAL_PINS];

extern const Dio_LevelType  ChannelLevel [TOTAL_PINS];

Std_ReturnType Det_ReportError(u16 moduleId,u8 instanceId,u8 ApiId,u8 ErrorId)
{
	return E_OK ;
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType Level;
	Dio_PortType PortId;
	PortId = ChannelId/NumOfPort;
	u8 Pin_num = ChannelId % NumOfPort ;
#if( DioDevErrorDetect==STD_OK)
	if(ChannelId>=TOTAL_PINS)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_ReadChannel_API,DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif
	switch(PortId)
	{
	case PA :
		if(READ_PIN(PINA_REG ,Pin_num)==STD_LOW )
		{
			Level=STD_LOW;
		}
		else
		{
			Level=STD_HIGH;
		}
		break;
	case PB :
		if(READ_PIN(PINB_REG ,Pin_num)==STD_LOW )
		{
			Level=STD_LOW;
		}
		else
		{
			Level=STD_HIGH;
		}
		break;
	case PC :
		if(READ_PIN(PINC_REG ,Pin_num)==STD_LOW )
		{
			Level=STD_LOW;
		}
		else
		{
			Level=STD_HIGH;
		}
		break;

	case PD :
		if(READ_PIN(PIND_REG ,Pin_num)==STD_LOW )
		{
			Level=STD_LOW;
		}
		else
		{
			Level=STD_HIGH;
		}
		break;

	}


	return Level;

}

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	Dio_PortType PortId;
	PortId = ChannelId/NumOfPort;
	u8 Pin_num = ChannelId %NumOfPort ;
#if( DioDevErrorDetect==STD_OK)
	if(ChannelId>=TOTAL_PINS)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_WriteChannel_API,DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif
	switch (PortId)
	{
	case PA:
		if(Level==STD_HIGH)
		{
			SET_PIN(PORTA_REG,Pin_num);
		}
		else if(Level==STD_LOW)
		{
			CLEAR_PIN(PORTA_REG,Pin_num);
		}
		break;

	case PB:
		if(Level==STD_HIGH)
		{
			SET_PIN(PORTB_REG,Pin_num);
		}
		else if(Level==STD_LOW)
		{
			CLEAR_PIN(PORTB_REG,Pin_num);
		}
		break;
	case PC:
		if(Level==STD_HIGH)
		{
			SET_PIN(PORTC_REG,Pin_num);
		}
		else if(Level==STD_LOW)
		{
			CLEAR_PIN(PORTC_REG,Pin_num);
		}
		break;
	case PD:
		if(Level==STD_HIGH)
		{
			SET_PIN(PORTD_REG,Pin_num);
		}
		else if(Level==STD_LOW)
		{
			CLEAR_PIN(PORTD_REG,Pin_num);
		}
		break;

	}
}

void Dio_WriteDirectionChannel(Dio_ChannelType ChannelId,Dio_ChannelStatus Status)
{
	Dio_PortType PortId;
	PortId = ChannelId/NumOfPort;
	u8 Pin_num = ChannelId % NumOfPort ;
#if( DioDevErrorDetect==STD_OK)
	if(ChannelId>=TOTAL_PINS)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_WriteDirctionChannel_API,DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif
	switch (PortId)
	{
	case PA:
		if(Status==OUTPUT)
		{
			SET_PIN(DDRA_REG,Pin_num);
		}
		else if(Status==INPUT)
		{
			CLEAR_PIN(DDRA_REG,Pin_num);
		}
		break;

	case PB:
		if(Status==OUTPUT)
		{
			SET_PIN(DDRB_REG,Pin_num);
		}
		else if(Status==INPUT)
		{
			CLEAR_PIN(DDRB_REG,Pin_num);
		}
		break;
	case PC:
		if(Status==OUTPUT)
		{
			SET_PIN(DDRC_REG,Pin_num);
		}
		else if(Status==INPUT)
		{
			CLEAR_PIN(DDRC_REG,Pin_num);
		}
		break;
	case PD:
		if(Status==OUTPUT)
		{
			SET_PIN(DDRD_REG,Pin_num);
		}
		else if(Status==INPUT)
		{
			CLEAR_PIN(DDRD_REG,Pin_num);
		}
		break;

	}

}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	Dio_PortLevelType Level;

#if( DioDevErrorDetect==STD_OK)
	if(PortId>PD)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_ReadPort_API,DIO_E_PARAM_INVALID_PORT_ID);
	}
#endif
	switch(PortId)
	{
	case PA:
		Level = PORTA_REG;
		break;
	case PB:
		Level = PORTB_REG;
		break;
	case PC:
		Level = PORTC_REG;
		break;
	case PD:
		Level = PORTD_REG;
		break;
	}
	return Level;
}

void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
{
#if( DioDevErrorDetect==STD_OK)
	if(PortId>PD)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_WritePort_API,DIO_E_PARAM_INVALID_PORT_ID);
	}
#endif
	switch(PortId)
	{
	case PA:
		PORTA_REG=Level;
		break;
	case PB:
		PORTB_REG=Level;
		break;
	case PC:
		PORTC_REG=Level;
		break;
	case PD:
		PORTD_REG=Level;
		break;
	}
}

void Dio_WriteDirectionPort(Dio_PortType PortId,Dio_ChannelStatus Status )
{
#if( DioDevErrorDetect==STD_OK)
	if(PortId>PD)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_WriteDirectionPort_API,DIO_E_PARAM_INVALID_PORT_ID);
	}
#endif
	switch(PortId)
	{
	case PA:
		DDRA_REG=Status;
		break;
	case PB:
		DDRB_REG=Status;
		break;
	case PC:
		DDRC_REG=Status;
		break;
	case PD:
		DDRD_REG=Status;
		break;
	}
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
	Dio_PortLevelType Level;

#if( DioDevErrorDetect==STD_OK)
	if(ChannelGroupIdPtr==NULL)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_ReadChannelGroup_API,DIO_E_PARAM_POINTER);
	}
#endif
   Level = (Dio_ReadChannel(ChannelGroupIdPtr->port)& (ChannelGroupIdPtr->mask))
		   >>(ChannelGroupIdPtr->offset);

	return Level;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level)
{
	Dio_WriteChannel(((ChannelGroupIdPtr->port) &(ChannelGroupIdPtr->mask))
			>>ChannelGroupIdPtr->offset,Level);
#if( DioDevErrorDetect==STD_OK)

	if(ChannelGroupIdPtr==NULL)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_WriteChannelGroup_API,DIO_E_PARAM_POINTER);
	}
#endif

}

#if( DioFlipChannelApi==STD_OK)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType Level;
	Dio_PortType PortId;
	PortId = ChannelId/NumOfPort;
	u8 Pin_num = ChannelId % NumOfPort ;
#if (DioDevErrorDetect==STD_OK)
	if(ChannelId>=TOTAL_PINS)
	{
		Det_ReportError(DIO_Driver,Instance,Dio_FlipChannel_API,DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif

	switch(PortId)
	{
	case PA:
		Level = TOGGLE_PIN(PORTA_REG,Pin_num);
		break;
	case PB:
		Level = TOGGLE_PIN(PORTB_REG,Pin_num);
		break;
	case PC:
		Level = TOGGLE_PIN(PORTC_REG,Pin_num);
		break;
	case PD:
		Level = TOGGLE_PIN(PORTD_REG,Pin_num);
		break;
	}
	return Level;
}

#endif

//Dio_WriteDirectionChannel(PINA0,ChannelType[PINA0]);

void Dio_Init(void)
{
	Dio_ChannelType ChannelId;
	for(ChannelId=PINA0_;ChannelId<TOTAL_PINS;ChannelId++)
	{
		Dio_WriteDirectionChannel(ChannelId,ChannelStatus[ChannelId]);
		Dio_WriteChannel(ChannelId,ChannelLevel[ChannelId]);
	}

}
