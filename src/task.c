//------------------------------------------------------------------
// FranRTOS ...
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------


//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------
#include "task.h"
#include "oskernel.h"

//------------------------------------------------------------------
// Global Constant Definitions
//------------------------------------------------------------------


//------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------


//------------------------------------------------------------------
// Local Variable Declarations
//------------------------------------------------------------------

// the task assignment to task control block start with index of 0
local uint16  index_to_assign = 0;
local uint32* next_stack_start = NON_IDLE_TASK_STACK_START;



//------------------------------------------------------------------
// Global Functions
//------------------------------------------------------------------

//
// configures a task handle with a corresponding tcb index.
// allocates a specified size of memory to the task
// sets the priority of the task used in priority-based preemptive scheduling
//
global void task_create (task_handle* handle, void (*task_handler)(void),
		uint16 stack_size, uint8 prio)
{

	uint8 j = 0;
	uint32* pointer = next_stack_start;

	handle->task_handler = task_handler;
 	handle->tcb_index = index_to_assign;

	user_tcbs[index_to_assign].task_state = TASK_READY_STATE;
	user_tcbs[index_to_assign].task_priority = prio;


	pointer -- ;
	*pointer = 0x01000000;

	pointer -- ;
	*pointer = (uint32)task_handler;

	pointer -- ;
	*pointer = 0xfffffffd;

	for (; j < 13; j++)
	{
		pointer -- ;
		*pointer = 0x0;
	}

	user_tcbs[index_to_assign].task_psp_val = pointer;

	index_to_assign++;
	num_tasks = index_to_assign;

	if(prio > highest_prio)
	{
		highest_prio = prio;
	}

	next_stack_start -= (16 + stack_size);

}

#if (SCHEDULER_TYPE == SCHEDULER_TYPE_RR) || (SCHEDULER_TYPE == SCHEDULER_TYPE_PP)

//
// Blocks a task from taking the CPU for a certain number of ticks
//
global void task_delay(task_handle* handle, uint16 tick_num)
{
	uint16	tcb_index;

	if(handle == NULL)
		tcb_index = current_task;
	else
		tcb_index = handle->tcb_index;

	user_tcbs[tcb_index].task_block_count = tick_num + global_ticks ;
	user_tcbs[tcb_index].task_state = TASK_BLOCKED_STATE;
	block_status |= (1 << tcb_index);
	sysctrl_regs->sysctrl_reg_icsr |= SYSCTRL_ICSR_PENDSVSET;
}

//
// Blocks a task indefinitely until task_unblock is called with the task's corresponding handle
//
global void task_block  (task_handle* handle)
{
	uint16 tcb_index = handle->tcb_index;
	user_tcbs[tcb_index].task_state = TASK_FORCED_BLOCKED_STATE;
	user_tcbs[tcb_index].task_block_count = 0;
	block_status |= (1u << tcb_index);
}

//
// Unblocks a task
//
global void task_unblock (task_handle* handle)
{
	uint16 tcb_index = handle->tcb_index;
	user_tcbs[tcb_index].task_state = TASK_READY_STATE;
	block_status &=~ (1u << tcb_index);
}

global void task_set_priority (task_handle* handle, uint8 priority)
{
	uint16 tcb_index = handle->tcb_index;
	user_tcbs[tcb_index].task_priority = priority;
	if(priority > highest_prio)
	{
		highest_prio = priority;
	}
	hi_prio_set = true;
}
#endif

#if SCHEDULER_TYPE == SCHEDULER_TYPE_SC

//
// Sets up a schedule table to perform a user-specified periodic scheduling procedure
// Called after a number of calls to task_create
//
global void task_set_static_cyclic_schedule (task_handle handle_array[], uint16 tick_array[])
{
	uint16 index;

	for(index = 0; index < num_tasks; index++)
	{
		tcb_index_sequence_table[index] = handle_array[index].tcb_index;
		task_ticks_table[index] = tick_array[index];
	}

	periodic_task_index = 0;
	current_periodic_task_ticks = 0;
	current_task = tcb_index_sequence_table[periodic_task_index];
}



#endif
