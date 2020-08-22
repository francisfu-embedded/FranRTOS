//------------------------------------------------------------------
// FranRTOS ...
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------

#ifndef OSKERNEL_H_
#define OSKERNEL_H_


//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------

#include "fran_rtos.h"

//------------------------------------------------------------------
// Package Variable Definitions
//------------------------------------------------------------------

//task control block structure
typedef struct
{
	uint32* task_psp_val;
	uint32  task_block_count;
	uint8   task_state;
	uint8   task_priority;
}   tcb;

package tcb user_tcbs[TASK_MAX_NUM];

// total number of tasks
package uint16 num_tasks;

// number of global ticks
package uint32 global_ticks;

// current task id
package uint32 current_task;

// a 16 bit status variable to mark the block/ready state of a task
package uint16 block_status ;

// an array of periodic task sequence
package uint16 tcb_index_sequence_table[TASK_MAX_NUM];

// an array of periodic task assigned execution ticks
package uint16 task_ticks_table[TASK_MAX_NUM];

// index of the currently executing periodic task
package uint16 periodic_task_index;

// number of ticks a current periodic task has been executed
package uint16 current_periodic_task_ticks;

//highest priority of all tasks
package uint8 highest_prio;

//highest priority just-set flag
package bool hi_prio_set;


//------------------------------------------------------------------
// Global Function Prototypes
//------------------------------------------------------------------
extern asfunc void kernel_scheduler_init (uint32* kernel_stack_start);
extern asfunc void kernel_scheduler_launch (void);


#endif /* OSKERNEL_H_ */
