// ------------------------------------------
//  Author: Woosung joung
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   April 07, 2023
// ------------------------------------------

#define csd_LED_ADDR 0x41200000


.extern csd_main

.global main
main:
	@ r1: led memory map address
	@ r5: led number that will be enlightened
	ldr r1, =csd_LED_ADDR	// load led memory map address
	ldr r5, =#1

loop:
	cmp r5, #0x00000100
	ldreq r5, =#1
	str r5, [r1]
	bl timeout_sw_based
	lsl r5, r5, #1
	b loop

.data
.align 4
