//------------------------------------------------------------------
// FranRTOS Header File
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------

#ifndef FRAN_RTOS_H_
#define FRAN_RTOS_H_

//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------
#include "fran_rtos_scope.h"

//------------------------------------------------------------------
// Global Constant Definitions
//------------------------------------------------------------------

//maximum number of tasks
#define TASK_MAX_NUM                               17

//commonly used stack sizes
#define STACK_SIZE_16                              16ul
#define STACK_SIZE_32                              32ul
#define STACK_SIZE_64                              64ul
#define STACK_SIZE_128                             128ul
#define STACK_SIZE_256                             256ul
#define STACK_SIZE_512                             512ul
#define STACK_SIZE_1024                            1024ul

//processor SRAM start and end
#define SRAM_START                                 0x20000000
#define SRAM_SIZE                                  (STACK_SIZE_128 * STACK_SIZE_1024)
#define SRAM_END           						   ((uint32*)(SRAM_START + SRAM_SIZE))

#define NON_IDLE_TASK_STACK_START                  SRAM_END
#define SCHEDULER_STACK_START                      ((uint32*)(NON_IDLE_TASK_STACK_START - TASK_MAX_NUM * STACK_SIZE_256))

//processor clock speed
#define CLK_SPEED_IN_HZ                            16000000
#define TICK_PRESC_SPEED_IN_HZ                     1000
#define SYSTICK_COUNT_VAL                          ((CLK_SPEED_IN_HZ / TICK_PRESC_SPEED_IN_HZ) - 1)


//scheduler types

#define	SCHEDULER_TYPE_RR                          0     //Round Robin Scheduler
#define	SCHEDULER_TYPE_SC                          1     //Static Cyclic Scheduler
#define	SCHEDULER_TYPE_PP 						   2     //Priority-based Preemptive Scheduler
#define	SCHEDULER_TYPE_NP 						   3     //Non-Preemptive Scheduler


//task priorities
enum task_priority
{
	TASK_PRIO_0,
	TASK_PRIO_1,
	TASK_PRIO_2,
	TASK_PRIO_3
};

//task states
enum task_name
{
	TASK_READY_STATE,
	TASK_BLOCKED_STATE,
	TASK_PRIORITY_BLOCKED_STATE,
	TASK_FORCED_BLOCKED_STATE
};

#define SCHEDULER_TYPE                             SCHEDULER_TYPE_PP


#endif /* FRAN_RTOS_H_ */
