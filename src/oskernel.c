//------------------------------------------------------------------
// FranRTOS ...
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------


//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------
#include "oskernel.h"
#include "task.h"

//------------------------------------------------------------------
// Local Constant Definitions
//------------------------------------------------------------------




//------------------------------------------------------------------
// Local Variable Declarations
//------------------------------------------------------------------


//de Bruijn look-up table for fast bit index searching
local const uint16 de_bruijn_lookup[32] = {0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9};


//Flag to indicate idle task is running
local bool idle_running = false;


//------------------------------------------------------------------
// Local Function Implementations
//------------------------------------------------------------------

//
// Quickly get the tcb index using the de Bruijn look-up table above with a 16-bit bit_holder
//
local const uint16 kernel_fast_fetch_tcb_index(uint16 bit_holder)
{
	uint16 index = de_bruijn_lookup[(uint16)((bit_holder * 0x77CB531ul) >> 27)];
	return index;
}

//
// Idle task to be run when all tasks are in blocked state. Suitable for the microcontroller to enter low-power mode
//
local void kernel_idle_thread(void)
{
	for(;;)
	{
		//implement low-power instructions here

	}
}

//
// Called as part of kernel_scheduler_init to initialize all required package variables
//
local void kernel_init_global_ticks_and_current_task(void)
{
	global_ticks = 0;
	current_task = 0;
	block_status = 0;
	highest_prio = 0;
	hi_prio_set = true;
}

//
// Initialize the Cortex-M systick timer with user/specified clocking info in fran_rtos.h
//
local void kernel_systick_init(void)
{
	systick_regs->systick_reg_rvr &=~ (0x00ffffff);

	systick_regs->systick_reg_rvr |= SYSTICK_COUNT_VAL;
	systick_regs->systick_reg_csr |= 7;
}

//
// Get the next process stack pointer value when performing context-switch
//
local uint32 * kernel_get_psp_val (void)
{
	//treat idle task and user task psp value separately
	if(idle_running == false)
		return user_tcbs[current_task].task_psp_val;
	else
		return user_tcbs[num_tasks - 1].task_psp_val;
}

//
// Save the current process stack pointer value when performing context-switch
//
local void kernel_save_psp_value ( uint32 * stack_addr)
{
	//treat idle task and user task psp value separately
	if(idle_running == false)
		user_tcbs[current_task].task_psp_val = stack_addr;
	else
		user_tcbs[num_tasks - 1].task_psp_val = stack_addr;
}

//
// Determines the next task to run based on the type of Rtos scheduler specified by the user
//
local void kernel_update_next_task ( uint32 * stack_addr)
{

	//----------------------------------------------------------------
	// Non-Priority-Based Round-Robin Scheduler
	//----------------------------------------------------------------
#if (SCHEDULER_TYPE == SCHEDULER_TYPE_RR) || (SCHEDULER_TYPE == SCHEDULER_TYPE_PP)
    uint16 temp;
    uint16 bit_holder;
	uint16 to_run_status;
	uint16 status_mask = (1u << (num_tasks - 1)) - 1;
	uint16 ready_status = (~block_status) & status_mask;
	uint16 runned_status_mask = (1u << (current_task+1)) - 1;


    //if all user tasks are blocked, get the idle task running
	if(ready_status == 0)
	{
        idle_running = true;
		return;
	}
	else
	{
		idle_running = false;
	}


	//if not, find the ready-to-run tasks by clearing the runned status bits
	to_run_status = ready_status & (~runned_status_mask);

	//set current_task to 0 and fast exit if it is the last running task that has been taken care of
	if(to_run_status == 0)
	{
		to_run_status = ready_status;
	}

	//make the first set bit in to_run_status cleared
	temp = to_run_status & (to_run_status - 1);

	//recover the "cleared" bit in a 16-bit bit holder
	bit_holder = temp ^ to_run_status;

	//fetch the corresponding current task based on the bit_holder variable
	current_task = kernel_fast_fetch_tcb_index(bit_holder);
#endif

	//----------------------------------------------------------------
	// Static Cyclic Scheduler
	//----------------------------------------------------------------

#if (SCHEDULER_TYPE == SCHEDULER_TYPE_SC)
	current_task = tcb_index_sequence_table[periodic_task_index];
#endif

}

//
// Called by the systick handler to update the global tick count
//

local void kernel_update_global_tick (void)
{
	global_ticks ++;
}

//
// Update blocked/unblocked status of the task control blocks by checking if the blocking tick count has passed
//
local void kernel_unblock_tasks(void)
{
	uint16 temp;
	uint16 bit_holder;
	uint16 block_index;
	uint16 status_copy = block_status;

	if(status_copy == 0)
		return;

	while (status_copy != 0)
	{
		//make the first set bit in status_copy cleared
		temp = status_copy & (status_copy - 1);

		//recover the "cleared" bit in a 16-bit bit holder
		bit_holder = temp ^ status_copy;

		//fast fetch the bit index, namely the blocked tcb index
		block_index = kernel_fast_fetch_tcb_index(bit_holder);

		//unblock a task if it is not in ready state and the block count is equal to global ticks
		if((user_tcbs[block_index].task_state == TASK_BLOCKED_STATE) &&
				(user_tcbs[block_index].task_block_count == global_ticks))
		{
				user_tcbs[block_index].task_state = TASK_READY_STATE;
				block_status &=~ bit_holder;
		}

		status_copy = temp;
	}
}

local void kernel_block_low_priority_tasks(void)
{
	uint16 tcb_index;
	for(tcb_index  = 0; tcb_index < (num_tasks - 1); tcb_index ++)
	{
		if(user_tcbs[tcb_index].task_priority < highest_prio)
		{
			user_tcbs[tcb_index].task_state = TASK_PRIORITY_BLOCKED_STATE;
			block_status |= (1u << tcb_index);
		}
		else
		{
			user_tcbs[tcb_index].task_state = TASK_READY_STATE;
			block_status &=~ (1u << tcb_index);
		}
	}
}

//
// Called in kernel_scheduler_launch to pend the system-provided idle tasks to the user task control block array
// before the the scheduler kicks off the first task
//

local void kernel_create_idle_task (void)
{
	task_create(&idle_task, &kernel_idle_thread, STACK_SIZE_16, TASK_PRIO_0);
}

//
// Called by the SVC handler in priority-based preemptive scheduling
//
local uint32* kernel_get_first_psp_val_in_pp (void)
{
	uint16 index;
	for (index = 0 ; index < num_tasks ; index++)
	{
		if(user_tcbs[index].task_priority== highest_prio)
		{
			current_task = index;
			return user_tcbs[index].task_psp_val;
		}
	}
}


//------------------------------------------------------------------
// GLobal Function Implementations
//------------------------------------------------------------------

global asfunc void kernel_scheduler_init (uint32* kernel_stack_start)
{
	//initialize main stack pointer with the start of kernel stack as specified by the user
	__asm volatile ("MSR MSP, R0");

	//initialize all the required package variables
	__asm volatile ("PUSH  {LR}");
	__asm volatile ("BL  kernel_init_global_ticks_and_current_task");
	__asm volatile ("POP  {LR}");

	__asm volatile ("BX LR");
}

global asfunc void kernel_scheduler_launch (void)
{

	// first disable interrupts
	__asm volatile ("CPSID i" : : : "memory");

	//create an idle task
	__asm volatile("PUSH {LR}");
	__asm volatile("BL kernel_create_idle_task");
	__asm volatile("POP {LR}");

	//get the next psp
    __asm volatile("PUSH {LR}");
    __asm volatile("BL kernel_get_psp_val");
    __asm volatile("POP {LR}");

    //let processor enter thumb state to allow for multi-threading
    __asm volatile("MSR PSP, R0");
    __asm volatile("MOV R0, #0x02");
    __asm volatile("MSR CONTROL, R0");

    //initialize systick
    __asm volatile("PUSH {LR}");
    __asm volatile("BL kernel_systick_init");
    __asm volatile("POP  {LR}");

    //enable interrupts
    __asm volatile ("CPSIE i" : : : "memory");

    //use the SVC handler to kick off the first task
    __asm volatile("SVC #4");

    __asm volatile("BX LR");
}


//------------------------------------------------------------------
// Kernel ISR Implementations
//------------------------------------------------------------------
package asfunc void PendSV_Handler (void)
{

	//save context of current task
    __asm volatile("MRS R0, PSP");
    __asm volatile("STMDB R0!, {R4-R11}");
    __asm volatile("PUSH {LR}");
    __asm volatile("BL kernel_save_psp_value");


    //get into next task
    __asm volatile("BL kernel_update_next_task");
    __asm volatile("BL kernel_get_psp_val");
    __asm volatile("LDMIA R0!, {R4-R11}");
    __asm volatile("MSR PSP, R0");

    //return
    __asm volatile("POP {LR}");
    __asm volatile("BX LR");
}


package void SysTick_Handler (void)
{
#if SCHEDULER_TYPE == SCHEDULER_TYPE_RR
	kernel_update_global_tick();
	kernel_unblock_tasks();

	//generate a PendSV exception to perform context-switch
	sysctrl_regs->sysctrl_reg_icsr |= SYSCTRL_ICSR_PENDSVSET;
#endif

#if SCHEDULER_TYPE == SCHEDULER_TYPE_SC
	kernel_update_global_tick();
	current_periodic_task_ticks++;

	//when a periodic task's assigned tick count is reached
	if(current_periodic_task_ticks == task_ticks_table[periodic_task_index])
	{
		//reset the current task tick count
		current_periodic_task_ticks = 0;

		//increment periodic task index for referencing task_ticks_table
		periodic_task_index++;

		//reset periodic task index if the end of tasks has been reached
		if(periodic_task_index > (num_tasks - 2))
			periodic_task_index = 0;

		//generate a PendSV exception to perform context-switch
		sysctrl_regs->sysctrl_reg_icsr |= SYSCTRL_ICSR_PENDSVSET;
	}
#endif

#if SCHEDULER_TYPE == SCHEDULER_TYPE_PP
	kernel_update_global_tick();
	kernel_unblock_tasks();

	if(hi_prio_set == true)
	{
		kernel_block_low_priority_tasks();
		hi_prio_set = false;
	}

	//generate a PendSV exception to perform context-switch
	sysctrl_regs->sysctrl_reg_icsr |= SYSCTRL_ICSR_PENDSVSET;
#endif

}

package asfunc void SVC_Handler(void)
{
#if SCHEDULER_TYPE==SCHEDULER_TYPE_RR
	// prepare the context of the first task and switch-in
	__asm volatile("PUSH {LR}");
	__asm volatile("BL kernel_get_psp_val");
	__asm volatile("LDMIA R0!, {R4-R11}");
	__asm volatile("MSR PSP, R0");
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
#endif

#if SCHEDULER_TYPE==SCHEDULER_TYPE_PP
	// prepare the context of the first high-priority task and switch-in
	__asm volatile("PUSH {LR}");
	__asm volatile("BL kernel_get_first_psp_val_in_pp");
	__asm volatile("LDMIA R0!, {R4-R11}");
	__asm volatile("MSR PSP, R0");
	__asm volatile("POP {LR}");

	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL kernel_block_low_priority_tasks");
	__asm volatile ("POP {LR}");


	__asm volatile("BX LR");
#endif

}
