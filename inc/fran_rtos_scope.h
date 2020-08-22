//------------------------------------------------------------------
// FranRTOS Scope File
// Author: Francis Fu, Volksingenieur der Industriepartei Chinas
// A small RTOS project for Arm Cortex M4/M3 based microcontrollers
//------------------------------------------------------------------

#ifndef FRAN_RTOS_SCOPE_H_
#define FRAN_RTOS_SCOPE_H_

//------------------------------------------------------------------
// Package Includes
//------------------------------------------------------------------
#include <stdio.h>

//------------------------------------------------------------------
// Type/Keyword definitions
//------------------------------------------------------------------
#define uchar  unsigned char
#define uint8  uint8_t
#define uint16 uint16_t
#define uint32 uint32_t
#define bool   uint8_t      //boolean type
#define local  static
#define global              //specifies a variable or function that could be accessed/called by user
#define package             //specifies a variable or function that could be accessed/called by packages that include current package
#define true   1
#define false  0
#define asfunc  __attribute__((naked)) //asm naked function
#define __vo volatile

//------------------------------------------------------------------
// Arm Cortex M4 Processor Core Registers Used
//------------------------------------------------------------------

#define SYSCTRL_ICSR_PENDSVSET                           (1ul << 28)

// Systick Timer Registers

typedef struct
{
	__vo uint32 systick_reg_csr;  // SysTick Control and Status Register
	__vo uint32 systick_reg_rvr;  // SysTick Reload Value Register
	__vo uint32 systick_reg_cvr;  // SysTick Current Value Register
	__vo uint32 systick_reg_calib;// SysTick Calibration Value Register
}   systick_reg;

#define systick_regs                                                 ((systick_reg*)0xE000E010)

// System Control Block

typedef struct
{
	__vo uint32 sysctrl_reg_cpuid;
	__vo uint32 sysctrl_reg_icsr;
	__vo uint32 sysctrl_reg_vtor;
	__vo uint32 sysctrl_reg_aircr;
	__vo uint32 sysctrl_reg_scr;
	__vo uint32 sysctrl_reg_ccr;
	__vo uint32 sysctrl_reg_shpr1;
	__vo uint32 sysctrl_reg_shpr2;
	__vo uint32 sysctrl_reg_shpr3;
	__vo uint32 sysctrl_reg_shcrs;
	__vo uint32 sysctrl_reg_cfsr;
	__vo uint32 sysctrl_reg_hfsr;
	__vo uint32 sysctrl_reg_rsvd;
	__vo uint32 sysctrl_reg_mmar;
	__vo uint32 sysctrl_reg_bfar;
	__vo uint32 sysctrl_reg_afsr;
}   sysctrl_reg;

#define sysctrl_regs                   								((sysctrl_reg*)0xE000ED00)



#endif /* FRAN_RTOS_SCOPE_H_ */
