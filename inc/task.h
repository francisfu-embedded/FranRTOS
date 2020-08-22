//------------------------------------------------------------------
// FranRTOS ...
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------

#ifndef TASK_H_
#define TASK_H_

#include "fran_rtos.h"

//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------


//------------------------------------------------------------------
// Global Constant Definitions
//------------------------------------------------------------------


//------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------

typedef struct
{
    void (* task_handler) (void);
    uint16 tcb_index;
}   task_handle;

// a idle_task
task_handle idle_task;

//------------------------------------------------------------------
// Local Variable Declarations
//------------------------------------------------------------------


//------------------------------------------------------------------
// GLobal Function Declarations
//------------------------------------------------------------------

extern void task_create (task_handle* handle, void (*task_handler)(void),
		uint16 stack_size, uint8 prio);


extern void task_delay  (task_handle* handle, uint16 tick_num);
extern void task_block  (task_handle* handle);
extern void task_unblock (task_handle* handle);
extern void task_set_priority (task_handle* handle, uint8 priority);


extern void task_set_static_cyclic_schedule (task_handle handle_array[], uint16 tick_array[]);

#endif /* TASK_H_ */
