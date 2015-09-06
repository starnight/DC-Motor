#include <stdio.h>
#include <avr/io.h>
#include "time.h"
#include "uart.h"

/* Define the maximum rotation speed according to the maximum duty cycle. */
#define MAXSPEED 255

/* Define rotation counts pin. */
#define SetCountPin()	(DDRD = 0<<DDD4)
#define StartCount()	(Timer0SetPrescaler(TIMER0_CLOCK_FROM_T0_FALLING_EDGE))
#define ReadCount()		(Timer0Read())
#define ClearCount()	(Timer0Clear())
/* Define system timer. */
#define SetPeriod(p)	(Timer1SetTop(p))	
#define StartSysTime()	(Timer1SetPrescaler(TIMER1_CLOCK_PRESCALER_D1024))
#define StopSysTime()	(Timer1Stop())
#define EnableTimeout()	(Timer1EnableOCAInterrupt())
/* Define PWM pin. */
#define SetPWMPin()			(DDRD = 1<<DDD3)
#define ConnectPWMPin()		(Timer2ConnectOC2B(PWM_PIN_CLEAR_ON_MATCH))
#define DisconnectPWMPin()	(Timer2ConnectOC2B(PWM_PIN_DISCONNECTED))
#define SetSpeed(s)			(Timer2SetTop(s % (MAXSPEED+1)))
#define StartPWM()			(Timer2SetPrescaler(TIMER2_CLOCK_PRESCALER_D256))
#define StopPWM()			(Timer2Stop())
#define ForcePWMLow()		(PORTD &= ~(1<<PORTD3))
/* Define rotation pin. */
#define SetDirectionPin()		(DDRD |= 1<<DDD2)
#define RotateClockwise()		(PORTD |= 1<<PORTD2)
#define RotateAntiClockwise()	(PORTD &= ~(1<<PORTD2))
/* Read command from UART. */
#define ReadCommand()			(USARTRead1ByteBlocking())

/* Called when system timeout. */
Timer1CompareAEvent() {
	char string[16];
	uint16_t count;

	count = ReadCount();
	ClearCount();
	sprintf(string, "Count = %03d\r\n", (int)count);
	UARTSendStream((uint8_t *)string);
}

int main(void)
{
	/* Allocate the space to store characters. */
	char string[32];
	uint8_t command;
	int16_t speed = 0;

	/* Disable rotation at begining. */
	StopPWM();

	/* Initial Timer/Counter0: Normal count with T0 falling edge. */
	Timer0Init();
	SetCountPin();
	ClearCount();
	/* Initial Timer/Counter1: CTC with 1024 prescaling. */
	Timer1Init();
	SetPeriod(F_CPU/1024);
	EnableTimeout();
	/* Initial Timer/Counter2: None-inverted fast PWM with no prescaling. */
	Timer2Init();
	SetPWMPin();
	SetSpeed(speed);
	StartPWM();

	/* Set rotate direction. */
	SetDirectionPin();
	RotateClockwise();

	/* Initial the UART. */
	USARTInit();
	
	/* Enable global interrupt flag. */
	sei();

	while(1)
	{
		/* Make the string. */
		sprintf(string, "%03d\r\n", (int)speed);

		/* Stream out the string by UART0. */
		UARTSendStream((uint8_t *)string);

		/* Wait and read a command. */
		command = ReadCommand();

		switch(command) {
			case '+':
				/* Increase speed. */
				if(speed < MAXSPEED) speed++;
				break;
			case '-':
				/* Decrease speed. */
				if(speed > -MAXSPEED) speed--;
				break;
			case 'c':
				/* Clear speed. */
				speed = 0;
				break;
			case 's':
				/* Start counting. */
				StartCount();
				StartSysTime();
				break;
		}

		/* Set speed and direction. */
		if(speed > 0) {
			ConnectPWMPin();
			SetSpeed(speed);
			RotateClockwise();
		}
		else if(speed < 0) {
			ConnectPWMPin();
			SetSpeed(-speed);
			RotateAntiClockwise();
		}
		else {
			/* For zero PWM duty of AVR. */
			DisconnectPWMPin();
			ForcePWMLow();
		}
	}

	return 0;
}
