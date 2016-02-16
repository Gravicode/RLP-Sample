/*
 *	Copyright (c) GHI Electronics, LLC.  All rights reserved.
 *	RLP support files.
 *  This file should not be changed under any condition.
 */

#ifndef _RLP_H_
#define _RLP_H_

#ifdef EMX
	#define RLP_ADDRESS 0xA0F00000
	#define RLP_SIZE 0x000FFFFC
#elif defined G120
	#define RLP_ADDRESS 0xA0F00000
	#define RLP_SIZE 0x000FFFFC
#elif defined G400
	#define RLP_ADDRESS 0xA0000000
	#define RLP_SIZE 0x16FFFFC
#elif defined CERB_FAMILY
	#define RLP_ADDRESS 0x2001EE00
	#define RLP_SIZE 0x0FFC
#else
	#error You must define your board before including RLP.h.
#endif

#define RLP_TRUE  1
#define RLP_FALSE 0

#define RLP_GPIO_NONE  0xFFFFFFFF

#define RLP_GPIO_INT_NONE 0
#define RLP_GPIO_INT_EDGE_LOW 1
#define RLP_GPIO_INT_EDGE_HIGH 2
#define RLP_GPIO_INT_EDGE_BOTH 3
#define RLP_GPIO_INT_LEVEL_HIGH 4 
#define RLP_GPIO_INT_LEVEL_LOW 5 

#define RLP_GPIO_RESISTOR_DISABLED 0
#define RLP_GPIO_RESISTOR_PULLDOWN 1
#define RLP_GPIO_RESISTOR_PULLUP 2

#define RLP_TASK_DATA_SIZE	32

typedef void (*RLP_CALLBACK_FPN)(void* arg);
typedef void (*RLP_GPIO_INTERRUPT_SERVICE_ROUTINE)(unsigned int pin, unsigned int pinState, void* param);

typedef struct 
{
	unsigned int data[RLP_TASK_DATA_SIZE / 4];
} RLP_Task;

typedef struct
{
	unsigned int GlitchFilterEnable;
	unsigned int IntEdge;
	unsigned int ResistorState;
} RLP_InterruptInputPinArgs;

typedef struct 
{
	unsigned int magic;
	unsigned int firmwareVersion;		
	unsigned int magicSize;
	
	struct
	{
		unsigned int (*Install)(unsigned int irqIndex, RLP_CALLBACK_FPN isr, void* isrParam);
		unsigned int (*Uninstall)(unsigned int irqIndex);
		unsigned int (*Disable)(unsigned int irqIndex);
		unsigned int (*Enable)(unsigned int irqIndex);
		unsigned int (*IsEnabled)(unsigned int irqIndex);
		unsigned int (*IsPending)(unsigned int irqIndex);
		unsigned int (*GlobalInterruptDisable)();
		unsigned int (*GlobalInterruptEnable)();
		unsigned int (*IsGlobalInterruptEnabled)();

	} Interrupt;

	struct
	{
		void (*EnableOutputMode)(unsigned int pin, unsigned int initialState);
		unsigned int (*EnableInputMode)(unsigned int pin, unsigned int resistorState);
		unsigned int (*EnableInterruptInputMode)(unsigned int pin, RLP_InterruptInputPinArgs* args, RLP_GPIO_INTERRUPT_SERVICE_ROUTINE isr, void* isrParam);
		unsigned int (*Readpin)(unsigned int pin);
		void (*Writepin)(unsigned int pin, unsigned int pinState);
		unsigned int (*Reservepin)(unsigned int pin, unsigned int reserve);
		unsigned int (*IsReserved)(unsigned int pin);
	} GPIO;
	
	void* (*malloc)(unsigned int length);
	void (*free)(void* ptr);
	void (*Delay)(unsigned int microSeconds);

	void* (*malloc_CustomHeap)(unsigned int length);
	void (*free_CustomHeap)(void* ptr);

	struct
	{
		void (*Initialize)(RLP_Task* task, RLP_CALLBACK_FPN taskCallback, void* arg, unsigned int isKernelMode);
		void (*Schedule)(RLP_Task* task);
		void (*ScheduleTimeOffset)(RLP_Task* task, unsigned int timeOffsetMicroseconds);
		void (*Abort)(RLP_Task* task);
		unsigned int (*IsScheduled)(RLP_Task* task);

	} Task;

	void (*PostManagedEvent)(unsigned int data);

} RLP_Extension_T;

#define RLP (*((RLP_Extension_T**)(RLP_ADDRESS + RLP_SIZE)))
#define RLP_EXT_MAGIC 0x73DE1BEA
#define RLP_MAGIC_SIZE sizeof(RLP_Extension_T)

#endif
