/*------------------------------------------------------------------------------
  Copyright (c) 2014 The Simple Oscilloscope Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/

#ifndef __AVR_ATMEGA328_TIMER_H__
#define __AVR_ATMEGA328_TIMER_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* Define PWM pin connecting mode. */
#define PWM_PIN_DISCONNECTED	0
#define PWM_PIN_TOGGLE_ON_MATCH	1
#define PWM_PIN_CLEAR_ON_MATCH	2
#define PWM_PIN_SET_ON_MATCH	3

/* Choose prescaler factor for timer#0 clock. */
#define TIMER0_NO_CLOCK_SOURCE				0
#define TIMER0_CLOCK_NO_PRESCALER			1
#define TIMER0_CLOCK_PRESCALER_D8			2
#define TIMER0_CLOCK_PRESCALER_D64			3
#define TIMER0_CLOCK_PRESCALER_D256			4
#define TIMER0_CLOCK_PRESCALER_D1024		5
#define TIMER0_CLOCK_FROM_T0_FALLING_EDGE	6
#define TIMER0_CLOCK_FROM_T0_RISING_EDGE	7

/* Enable timer#0 output compare A match interrupt. */
#define Timer0EnableOCAInterrupt()	(TIMSK0 |= (1 << OCIE0A))
/* Disable timer#0 output compare A match interrupt. */
#define Timer0DisableOCAInterrupt()	(TIMSK0 &= ~(1 << OCIE0A))
/* Enable timer#0 output compare B match interrupt. */
#define Timer0EnableOCBInterrupt()	(TIMSK0 |= (1 << OCIE0B))
/* Disable timer#0 output compare B match interrupt. */
#define Timer0DisableOCBInterrupt()	(TIMSK0 &= ~(1 << OCIE0B))
/* Enable timer#0 overflow interrupt. */
#define Timer0EnableOVInterrupt() (TIMSK0 |= (1 << TOIE0))
/* Disable timer#0 overflow interrupt. */
#define Timer0DisableOVInterrupt() (TIMSK0 &= ~(1 << TOIE0))
/* Initial timer#0 with Fast PWM mode. */
#define Timer0Init() ({ \
	/* Set timer#0 normal mode.*/ \
	TCCR0A = (0 << WGM01) | (0 << WGM00) | (0 << COM0A0); \
	TCCR0B = (TCCR0B & 0xE7) | (0 << WGM02); \
	/* Zero timer#0 counter. */ \
	TCNT0 = 0; })
/* Set the clock prescaler for timer#0 clock. */
#define Timer0SetPrescaler(prescaler)	(TCCR0B = (TCCR0B & 0xF8) | prescaler)
/* Set the counting TOP for timer#0. */
#define Timer0SetTop(top)	(OCR0A = top - 1)
/* Read timer#0. */
#define Timer0Read()	(TCNT0)
/* Clear timer#0. */
#define Timer0Clear()	(TCNT0 = 0)
/* Stop timer#0 counting. */
#define Timer0Stop()	(Timer0SetPrescaler(TIMER0_NO_CLOCK_SOURCE))
/* Define the interrupt service routine for timer#0 comparing A matched. */
#define Timer0CompareAEvent()	ISR(TIMER0_COMPA_vect)
/* Define the interrupt service routine for timer#0 comparing B matched. */
#define Timer0CompareBEvent()	ISR(TIMER0_COMPB_vect)

/* Choose prescaler factor for timer#1 clock. */
#define TIMER1_NO_CLOCK_SOURCE				0
#define TIMER1_CLOCK_NO_PRESCALER			1
#define TIMER1_CLOCK_PRESCALER_D8			2
#define TIMER1_CLOCK_PRESCALER_D64			3
#define TIMER1_CLOCK_PRESCALER_D256			4
#define TIMER1_CLOCK_PRESCALER_D1024		5
#define TIMER1_CLOCK_FROM_T1_FALLING_EDGE	6
#define TIMER1_CLOCK_FROM_T1_RISING_EDGE	7

/* Enable timer#1 output compare A match interrupt. */
#define Timer1EnableOCAInterrupt()	(TIMSK1 |= (1 << OCIE1A))
/* Disable timer#1 output compare A match interrupt. */
#define Timer1DisableOCAInterrupt()	(TIMSK1 &= ~(1 << OCIE1A))
/* Enable timer#1 output compare B match interrupt. */
#define Timer1EnableOCBInterrupt()	(TIMSK1 |= (1 << OCIE1B))
/* Disable timer#1 output compare B match interrupt. */
#define Timer1DisableOCBInterrupt()	(TIMSK1 &= ~(1 << OCIE1B))
/* Enable timer#1 overflow interrupt. */
#define Timer1EnableOVInterrupt() (TIMSK1 |= (1 << TOIE1))
/* Disable timer#1 overflow interrupt. */
#define Timer1DisableOVInterrupt() (TIMSK1 &= ~(1 << TOIE1))
/* Initial timer#1 with Fast PWM mode. */
#define Timer1Init() ({ \
	/* Set timer#1 CTC mode.*/ \
	TCCR1A = (0 << WGM11) | (0 << WGM10) | (0 << COM1A0); \
	TCCR1B = (TCCR1B & 0xF7) | (0 << WGM13) | (1 << WGM12); \
	/* Zero timer#1 counter. */ \
	TCNT1 = 0; })
/* Set the clock prescaler for timer#1 clock. */
#define Timer1SetPrescaler(prescaler)	(TCCR1B = (TCCR1B & 0xF8) | prescaler)
/* Set the counting TOP for timer#1. */
#define Timer1SetTop(top)	(OCR1A = top - 1)
/* Read timer#1. */
#define Timer1Read()	(TCNT1)
/* Clear timer#1. */
#define Timer1Clear()	(TCNT1 = 0)
/* Stop timer#1 counting. */
#define Timer1Stop()	(Timer0SetPrescaler(TIMER0_NO_CLOCK_SOURCE))
/* Define the interrupt service routine for timer#1 comparing A matched. */
#define Timer1CompareAEvent()	ISR(TIMER1_COMPA_vect)
/* Define the interrupt service routine for timer#1 comparing B matched. */
#define Timer1CompareBEvent()	ISR(TIMER1_COMPB_vect)

/* Choose prescaler factor for timer#2 clock. */
#define TIMER2_NO_CLOCK_SOURCE				0
#define TIMER2_CLOCK_NO_PRESCALER			1
#define TIMER2_CLOCK_PRESCALER_D8			2
#define TIMER2_CLOCK_PRESCALER_D32			3
#define TIMER2_CLOCK_PRESCALER_D64			4
#define TIMER2_CLOCK_PRESCALER_D128			5
#define TIMER2_CLOCK_PRESCALER_D256			6
#define TIMER2_CLOCK_PRESCALER_D1024		7

/* Enable timer#2 output compare A match interrupt. */
#define Timer2EnableOCAInterrupt()	(TIMSK2 |= (1 << OCIE2A))
/* Disable timer#2 output compare A match interrupt. */
#define Timer2DisableOCAInterrupt()	(TIMSK2 &= ~(1 << OCIE2A))
/* Enable timer#2 output compare B match interrupt. */
#define Timer2EnableOCBInterrupt()	(TIMSK2 |= (1 << OCIE2B))
/* Disable timer#2 output compare B match interrupt. */
#define Timer2DisableOCBInterrupt()	(TIMSK2 &= ~(1 << OCIE2B))
/* Enable timer#2 overflow interrupt. */
#define Timer2EnableOVInterrupt() (TIMSK2 |= (1 << TOIE2))
/* Disable timer#2 overflow interrupt. */
#define Timer2DisableOVInterrupt() (TIMSK2 &= ~(1 << TOIE2))
/* Define timer#2 PWM pin mode. */
#define Timer2ConnectOC2A(mode) (TCCR2A = (TCCR2A & ~(3<<COM2A0)) \
                                           | (mode<<COM2B0))
#define Timer2ConnectOC2B(mode) (TCCR2A = (TCCR2A & ~(3<<COM2B0)) \
                                           | (mode<<COM2B0))
/* Initial timer#2 with Fast PWM mode. */
#define Timer2Init() ({ \
	/* Set timer#2 A fast PWM mode.*/ \
	TCCR2A = (1 << WGM21) | (1 << WGM20) | (PWM_PIN_CLEAR_ON_MATCH << COM2B0); \
	TCCR2B = (TCCR2B & 0xF7) | (0 << WGM22); \
	/* Zero timer#2 counter. */ \
	TCNT2 = 0; })
/* Set the clock prescaler for timer#2 clock. */
#define Timer2SetPrescaler(prescaler)	(TCCR2B = (TCCR2B & 0xF8) | prescaler)
/* Set the counting TOP for timer#2. */
#define Timer2SetTop(top)	(OCR2B = top - 1)
/* Read timer#2. */
#define Timer2Read()	(TCNT2)
/* Clear timer#2. */
#define Timer2Clear()	(TCNT2 = 0)
/* Stop timer#2 counting. */
#define Timer2Stop()	(Timer2SetPrescaler(TIMER2_NO_CLOCK_SOURCE))
/* Define the interrupt service routine for timer#2 comparing A matched. */
#define Timer2CompareAEvent()	ISR(TIMER2_COMPA_vect)
/* Define the interrupt service routine for timer#0 comparing B matched. */
#define Timer2CompareBEvent()	ISR(TIMER2_COMPB_vect)

#endif

