/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#include <stdio.h>
#include "Dio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "usart_driver.h"
#include "Platform_Types.h"
#include "LCD.h"
#include "LcdService.h"
#include "LCD_Cfg.h"
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL


//Funcation Declarion
void system_init(void);
void T_CameraAlarm(void*p);
void T_LcdDisplay(void*p);
void T_DetectDistance(void *p);
void T_MotorStopping(void*p);
void T_ReturnMoving(void*p);
void T_CameraDetect (void*p);

//Macros for Events
#define EventCamera          1<<0
#define EventStop            1<<1
#define EventDistance        1<<2
#define EventReturnMoving    1<<3

//Events Defition
EventGroupHandle_t Events=NULL;
EventBits_t  Bits;

//Tasks Difations
TaskHandle_t TaskCamera=NULL;
TaskHandle_t TaskCameraAlarm=NULL;
TaskHandle_t TaskLcdDisplay=NULL;
TaskHandle_t TaskDetectDistance=NULL;
TaskHandle_t TaskMotorStopping=NULL;
TaskHandle_t TaskReturnMoving=NULL;
TaskHandle_t TaskMotorMovig=NULL;

//Distace Difation
u8 Disatnce1=0;
u8 Disatnce2=0;

int main (void)
{
	//init priphral
	system_init();          //init program

	//Creat Event
	Events=xEventGroupCreate();

	//Creat Tasks

	xTaskCreate(T_CameraAlarm,NULL,100,NULL,6,&TaskCameraAlarm);
	xTaskCreate(T_LcdDisplay,NULL,150,NULL,4,&TaskLcdDisplay);
	xTaskCreate(T_DetectDistance,NULL,150,NULL,1,&TaskDetectDistance);
	xTaskCreate(T_MotorStopping,NULL,150,NULL,5,&TaskMotorStopping);
	xTaskCreate(T_ReturnMoving,NULL,100,NULL,2,&TaskReturnMoving);
	xTaskCreate(T_CameraDetect,NULL,100,NULL,3,&TaskCamera);


	//Start Schedule
	vTaskStartScheduler();

	while(1);


	return 0;
}
void system_init(void)
{
	DDRB=0b00000110;

	usart_init(9600);
	usart_puts("Started\r\n");
	Dio_Init();
	LCD_init();

}

//This task to stop Motor when and distance <50 cm
void T_MotorStopping(void*p)
{
	usart_puts("T_MotorStopping Started\r\n");
	while(1)
	{
		Bits=xEventGroupWaitBits(Events,EventStop,1,0,portMAX_DELAY);
		if((Bits&EventStop)==(EventStop))
		{
			PORTB=0x2;
			Bits=xEventGroupSetBits(Events,EventReturnMoving);
		}
	}
}

//This Task detect distance
void T_DetectDistance(void *p)
{
	usart_puts("T_DetectDistance\r\n");
	u8 distance1=0;
	u8 distance2=0;
	while(1)
	{
		PORTB=4;
		distance1=usart_getc();
		distance2=usart_getc();
		Disatnce1=distance1;
		Disatnce2=distance2;
		usart_putc(distance1);
		usart_putc(distance2);

		if((distance1>='5'))
		{

			Bits=xEventGroupSetBits(Events,EventDistance);

		}
		if((distance1<'5'))
		{

			Bits=xEventGroupSetBits(Events,EventStop);

		}
	}

}

//This task display the result
void T_LcdDisplay(void *p)
{
	usart_puts("T_LcdDisplay\r\n");
	while(1)
	{
		Bits=xEventGroupWaitBits(Events,EventCamera|EventStop|EventReturnMoving|EventDistance,1,0,portMAX_DELAY);
		if((Bits&EventCamera)==(EventCamera))
		{

			LCD_Clear();
			LCD_CursorMove(1,0);
			LCD_WriteString("Accidant happen");
		}
		if((Bits&EventStop)==(EventStop))
		{
			LCD_Clear();
			LCD_CursorMove(1,0);
			LCD_WriteString("Distance<50 cm");
			LCD_CursorMove(2,0);
			LCD_WriteString("Distance is=");
			LCD_WriteData(Disatnce1);
			LCD_WriteData(Disatnce2);
			_delay_ms(1000);
		}
		if((Bits&EventReturnMoving)==(EventReturnMoving))
		{
			LCD_Clear();
			LCD_CursorMove(1,0);
			LCD_WriteString("Return Moving");
		}

		if((Bits&EventDistance)==(EventDistance))
		{
			LCD_Clear();
			LCD_WriteString("Distance>=50 Cm");
			LCD_CursorMove(2,0);
			LCD_WriteString("Distance is=");
			LCD_WriteData(Disatnce1);
			LCD_WriteData(Disatnce2);
		}
	}
}

//This task when an accidant happen alarm will work
void T_CameraAlarm(void*p)
{
	usart_puts("T_CameraAlarm\r\n");
	while(1)
	{

		Bits=xEventGroupWaitBits(Events,EventCamera,1,0,portMAX_DELAY);
		if((Bits&EventCamera)==(EventCamera))
		{
			PORTB=0x2;
			vTaskDelay(1000);
			Bits=xEventGroupSetBits(Events,EventReturnMoving);

		}

	}
}

//This task when camera detect accident
void T_CameraDetect (void*p)
{
	usart_puts("T_CameraDetect\r\n");

	while(1)
	{
		PORTB=4;
	    if((PINB&0x1))
		{

			Bits=xEventGroupSetBits(Events,EventCamera);

			while((PINB&0x1))
			{
				vTaskDelay(10);
			}
		}
	    vTaskDelay(50);
	}
}

//when motor stop the car return to moving
void T_ReturnMoving(void*p)
{
	usart_puts("Return Moving\r\n");
	while(1)
	{
		Bits=xEventGroupWaitBits(Events,EventReturnMoving,1,0,portMAX_DELAY);

		if((Bits&EventReturnMoving)==(EventReturnMoving))
		{
			PORTB=0x4;
		}

	}

}
