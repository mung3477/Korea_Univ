// ------------------------------------------
//  Author: Woosung joung
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   April 13, 2023
// ------------------------------------------

#include "uart_init.s"
#include "uart_debug.S"
#define csd_LED_ADDR 0x41200000

.extern csd_main

.global main

main:

.data
.align 4

Input_data:	.word 2, 0, -7, -1, 3, 8, -4, 10
			.word -9, -16, 15, 13, 1, 4, -3, 14
			.word -8, -10, -15, 6, -13, -5, 9, 12
			.word -11, -14, -6, 11, 5, 7, -2, -12

Output_data:	.word 0, 0, 0, 0, 0, 0, 0, 0
				.word 0, 0, 0, 0, 0, 0, 0, 0
				.word 0, 0, 0, 0, 0, 0, 0, 0
				.word 0, 0, 0, 0, 0, 0, 0, 0
.text

	UART_init			// UART initialization
	UART_debug

	@ r0: input data pointer
	@ r1: output data pointer
	@ r2: count copied data (0 -> 32)
	@ r3: value at r0

 	ldr r0, =Input_data
 	UART_debug
 	ldr r1, =Output_data
 	UART_debug
	ldr r2, =#0
	UART_debug

copy:
	cmp	r2, #32
	bhs sort			// compare r2 with 32. If r2 >= 32, break the loop.
	ldr r3, [r0]		// load value at r0(address) to r3
	str r3, [r1]		// copy data at r0 to the address pointed by r1
	add r0, r0, #4
	add r1, r1, #4		// move r0, r1 to next data
	add r2, r2, #1		// increase copied data
	b copy				// loop

sort:
	@ r0: output data pointer
	@ r1: index of the last unsorted data (31 -> 0)
	@ r2: address of the iterator on array
	@ r3: index of r2 (i)
	@ r4: value of [i]
	@ r5: value of [i + 1]

 	ldr r0, =Output_data
	ldr r1, =#31
	UART_debug

loop:
	cmp r1, #0
	bls forever		// if the index of last unsorted data is 0, stop sorting.
	mov r2, r0		// starts with the first element of given array
	ldr r3, =#0		// initialize iterator index with 0

inner_loop:
	cmp r3, r1
	UART_debug
	bhs end_inner_loop	// if the iterator meets last unsorted data, break the loop.
	ldr r4, [r2]		// load the value at iterator address
	ldr r5, [r2, #4]	// load the value right next to the address of iterator(r2 + 4)
	UART_debug
	cmp r4, r5
	blgt swap			// if [i] > [i+1], swap both
	add r2, r2, #4		// move iterator address to next data
	add r3, r3, #1		// increase the index of iterator
	UART_debug
	b inner_loop		// loop

swap:
	str r5, [r2]		// write smaller one on left address
	str r4, [r2, #4]	// write larger one on right address
	UART_debug
	mov pc, r14			// return

end_inner_loop:
	sub r1, r1, #1		// decrease the index of last unsorted data
	b loop				// sort again

forever:
	UART_debug
	nop
 	b forever
