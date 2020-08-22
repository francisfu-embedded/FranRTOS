
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "oskernel.h"
#include "task.h"
#include "led.h"

uint16 count1 = 0;
uint16 count2 = 0;
uint16 count3 = 0;
uint16 count4 = 0;

void task1(void);
void task2(void);
void task3(void);
void task4(void);

task_handle handle_array[4];


int main(void)
{
	kernel_scheduler_init(SCHEDULER_STACK_START);
	led_init_all();

	task_create(&handle_array[0], &task1, STACK_SIZE_128, TASK_PRIO_1);
	task_create(&handle_array[1], &task2, STACK_SIZE_128, TASK_PRIO_2);
	task_create(&handle_array[2], &task3, STACK_SIZE_128, TASK_PRIO_2);
	task_create(&handle_array[3], &task4, STACK_SIZE_128, TASK_PRIO_1);
	kernel_scheduler_launch();

	for(;;);
}

void task1 (void)
{
   for(;;)
   {
	   count1++;
   }

}
void task2 (void)
{
	for(;;)
	{

		led_on(LED_GREEN);
		task_delay(NULL,1000);
		led_off(LED_GREEN);
		task_delay(NULL,1000);


	}
}

void task3 (void)
{
	for(;;)
	{
		count3 ++ ;
		led_on(LED_RED);
		task_delay(NULL,500);
		led_off(LED_RED);
		task_delay(NULL,500);

		if(count3 == 5)
		{
			task_set_priority(&handle_array[3], TASK_PRIO_3);
	    }

		if(count3 == 10)
		{
			task_set_priority (&handle_array[2], TASK_PRIO_2);
		}
	}

}

void task4 (void)
{
	for(;;)
	{
		count4 ++;
		led_on(LED_BLUE);
		task_delay(NULL,250);
		led_off(LED_BLUE);
		task_delay(NULL,250);
		if(count4 == 20)
		{
			task_set_priority(&handle_array[2], TASK_PRIO_3);
			task_set_priority(&handle_array[1], TASK_PRIO_3);
		}

	}
}


