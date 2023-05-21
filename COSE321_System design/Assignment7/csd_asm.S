// ------------------------------------------
//  Author: Woosung joung
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   May 22, 2023
// ------------------------------------------

#include "csd_zynq_peripherals.h"
#define csd_SW_ADDR 0x41210000

.extern csd_main

.global main
main:

	// Read Cache Type Register (CTR)
	mrc p15, 0, r1, c0, c0, 1

	// Read Cache Level ID Register (CLIDR)
	mrc p15, 1, r2, c0, c0, 1

	ldr r3, =#0x41210000
	ldr r4, [r3]
	and r4, r4, #1
	cmp r4, #1
	beq enable_cache
///*
	@------------------------
	@ Disable Caches (L2)
	@------------------------
	ldr r0, =L2_reg1_ctrl
	mov r1, #0x0
	str r1, [r0]
	@------------------------
	@ Disable Caches (IL1, DL1)
	@------------------------
	mrc		p15, 0, r0, c1, c0, 0	@ read control register (CP15 register1)
	bic		r0, r0, #4096		    @ disable I bit (Instruction Cache)
	bic		r0, r0, #4		        @ disable C bit (Data and Unified Caches)
	mcr		p15, 0, r0, c1, c0, 0	@ write control register (CP15 register2)
//*/
	b cache_done

enable_cache:
	@------------------------
	@ Enable Caches (L2)
	@------------------------
	ldr r0, =L2_reg1_ctrl
    mov r1, #0x1
    str r1, [r0]

	@------------------------
	@ Enable Caches (IL1, DL1)
	@------------------------
	mrc		p15, 0, r0, c1, c0, 0	@ read control register (CP15 register1)
	orr		r0, r0, #(1<<12)	    @ Enable I bit (Instruction Cache)
	orr		r0, r0, #(1<<2)         @ Enable C bit (Data and Unified Caches)
	mcr		p15, 0, r0, c1, c0, 0	@ write control register (CP15 register2)


cache_done:
	// read SCTLR (System Control Register) to r0
	mrc	p15, 0, r0, c1, c0, 0

	bl  csd_main

	b main
