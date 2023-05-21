// ------------------------------------------
//  Author: Woosung joung
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   May 10, 2023
// ------------------------------------------

#include "csd_zynq_peripherals.h"
#include "uart_init.s"

#define	TIMER_INITIAL	0x4189

// Vector table base location should be aligned at 2^5
.align 5
// --------------------------
// Our interrupt vector table
// --------------------------
csd_vector_table:
	b .
	b .
	b .
	b .
	b .
	b .
	b csd_IRQ_ISR
	b .

.extern task1_c
.extern task2_c
.extern task3_c

.global main
main:

	// Disable interrupt: CPSR'I = 1
	cpsID i

	cps #0x12	   	       // IRQ mode
	ldr	r13,=irq_stack_top // Stack pointer setup for IRQ mode

	cps #0x13		          // supervisor mode

	// ----------------------------
// TCB setup for each user program - Begin
// ----------------------------

	// task1 pcb setup
	ldr r1, =task1_c
	// consider LR adjustment of ISR
	add r1, r1, #4
	ldr r2, =task1_stack_top
	ldr r3, =task1_pcb_pointer
	//user mode SPSR
	ldr r4, =#0x10

	str r1, [r3, #-4]
	str r2, [r3, #52]
	str r4, [r3, #-8]

	// task2 pcb setup
	ldr r1, =task2_c
	// consider LR adjustment of ISR
	add r1, r1, #4
	ldr r2, =task2_stack_top
	ldr r3, =task2_pcb_pointer
	//user mode SPSR
	ldr r4, =#0x10

	str r1, [r3, #-4]
	str r2, [r3, #52]
	str r4, [r3, #-8]

	// task3 pcb setup
	ldr r1, =task3_c
	// consider LR adjustment of ISR
	add r1, r1, #4
	ldr r2, =task3_stack_top
	ldr r3, =task3_pcb_pointer
	// user mode SPSR
	ldr r4, =#0x10

	str r1, [r3, #-4]
	str r2, [r3, #52]
	str r4, [r3, #-8]

// ----------------------------
// TCB setup for each user program - End
// ----------------------------

	ldr	r13,=svc_stack_top // Stack pointer setup for SVC mode
	cps #0x1F				// SYS mode

	// -------------------------------------
	// Set VBAR (Vector Base Address Register) to
	// the base location of our interrupt vector table
	// -------------------------------------
	ldr     r0, =csd_vector_table
	mcr     p15, 0, r0, c12, c0, 0
	dsb
	isb

	// Enable interrupt: CPSR'I = 0
	cpsIE i

// ---------------------------
// Generic Interrupt Controller (GIC) setup - Begin
// ---------------------------

	// CPU Interface ID Register
	ldr r0, =GICC_IIDR
	ldr r3, [r0]

	// CPU Controller Type Register
	ldr r0, =GICD_TYPER
	ldr r3, [r0]

	// CPU Binary Pointer Register
	ldr r0, =GICC_BPR
	ldr r3, [r0]

	// Distributor Control Register
	ldr r0, =GICD_CTLR
	ldr r1, [r0]
	mov r2, #1       // Enable
	orr r1, r1, r2
	str r1, [r0]
	ldr r3, [r0]

	 // Interrupt Set-Enable Register 0
	ldr r0, =GICD_ISENABLER0
	ldr r1, [r0]
	mov r2, #1 << 29   // Enable #29 (Private Timer)
	orr r1, r1, r2
	str r1, [r0]
	ldr r3, [r0]

	// According to specifications,
	// Cortex-A9 supports 5-bit version of priority format [7:3] in secure world
	// ( 0 -> 8 -> 16 -> 24...)

	// Interrupt Priority Register #7
	ldr r0, =GICD_PRIOR7
	ldr r1, [r0]
	mov r2, #0x10 << 8    // Priority 16 for ID# 29 (Private Timer)
	orr r1, r1, r2
	str r1, [r0]
	ldr r3, [r0]

	// CPU Interface Control Register
	ldr r0, =GICC_CTLR
	ldr r1, [r0]
	mov r2, #1        // Enable
	orr r1, r1, r2
	str r1, [r0]
	ldr r3, [r0]

 	// CPU Interface Interrupt Priority Mask Register
	ldr r0, =GICC_PMR
	ldr r1, [r0]
	mov r2, #0xFF     // Lowest
	orr r1, r1, r2
	str r1, [r0]
	ldr r3, [r0]

// ---------------------------
// Generic Interrupt Controller (GIC) setup - End
// ---------------------------

// ---------------------------
// Private Timer setup - Begin
// ---------------------------

 	// Private Timer Load Register
	ldr r0, =PRIVATE_LOAD
 	ldr r1, =TIMER_INITIAL
 	str r1, [r0]

 	// Private Timer Control Register
  	ldr r0, =PRIVATE_CONTROL
 	mov r1, #10 << 8   // Prescalar
 	orr r1, r1, #7     // IRQ Enable, Auto-Reload, Timer Enable
 	str r1, [r0]

// ----------------------------
// Private Timer setup - End
// ----------------------------

	UART_init     // UART Initialization

	// Change to user mode
	cps #0x10

	// set current task number to 1
	ldr r1, =cur_task
	ldr r2, =#1
	str r2, [r1]
	ldr sp, =task1_stack_top
	b task1_c

// ----------------------------
// Interrupt Service Routines (ISRs) - Begin
// ----------------------------

csd_IRQ_ISR:

	// Store current registers (except stack pointer) in IRQ stack
	stmfd sp!, {r0-r12}
	mrs r0, spsr
	stmfd sp!, {r0, lr}

 	// Interrupt Ack
  	ldr r0, =GICC_IAR
	ldr r3, [r0]

	// Clear Interrupt Status bit
  	ldr r0, =PRIVATE_STATUS
  	mov r1, #1
	str r1, [r0]

 	// End-of-Interrupt
  	ldr r0, =GICC_EOIR
	str r3, [r0]

	ldr r0, =cur_task
	ldr r1, [r0]

	cmp r1, #1
	beq sched_task2

	cmp r1, #2
	beq sched_task3

sched_task1:
	// Change current task number to 1
	ldr r1, =#1
	str r1, [r0]

	// Store current task3's pcb
	ldr r0, =task3_pcb_pointer
	// Store spsr, lr
	ldmfd sp!, {r1, r2}
	stmdb r0, {r1, r2}
	// Store other registers
	ldmfd sp!, {r0-r12}
	ldr sp, =task3_pcb_pointer
	stmia sp, {r0-lr}^

	// Restore pcb's user registers
	ldr sp, =task1_pcb_pointer
	ldmdb sp, {r0, lr}
	msr spsr, r0
	ldmia sp, {r0-lr}^

	// Restore IRQ stack pointer for next ISR
	ldr sp, =irq_stack_top
	// Return to task1
	subs pc, lr, #4

sched_task2:
	// Change current task number to 2
	ldr r1, =#2
	str r1, [r0]

	// Store current task1's pcb
	ldr r0, =task1_pcb_pointer
	// Store spsr, lr
	ldmfd sp!, {r1, r2}
	stmdb r0, {r1, r2}
	// Store other registers
	ldmfd sp!, {r0-r12}
	ldr sp, =task1_pcb_pointer
	stmia sp, {r0-lr}^

	// Restore pcb's user registers
	ldr sp, =task2_pcb_pointer
	ldmdb sp, {r0, lr}
	msr spsr, r0
	ldmia sp, {r0-lr}^

	// Restore IRQ stack pointer
	ldr sp, =irq_stack_top
	// Return to task2
	subs pc, lr, #4

sched_task3:
	// Change current task number to 3
	ldr r1, =#3
	str r1, [r0]

	// Store current task2's pcb
	ldr r0, =task2_pcb_pointer
	// Store spsr, lr
	ldmfd sp!, {r1, r2}
	stmdb r0, {r1, r2}
	// Store other registers
	ldmfd sp!, {r0-r12}
	ldr sp, =task2_pcb_pointer
	stmia sp, {r0-lr}^

	// Restore pcb's user registers
	ldr sp, =task3_pcb_pointer
	ldmdb sp, {r0, lr}
	msr spsr, r0
	ldmia sp, {r0-lr}^

	// Restore IRQ stack pointer
	ldr sp, =irq_stack_top
	// Return to task3
	subs pc, lr, #4

// ----------------------------
// Interrupt Service Routines (ISRs) - End
// ----------------------------

.data
.align 4

irq_stack:     .space 1024
irq_stack_top:
svc_stack:     .space 1024
svc_stack_top:
task1_stack:	.space 1024
task1_stack_top:
task2_stack:	.space 1024
task2_stack_top:
task3_stack:	.space 1024
task3_stack_top:

task1_pcb:	.space 8
task1_pcb_pointer:	.space 60
task2_pcb:	.space 8
task2_pcb_pointer:	.space 60
task3_pcb:	.space 8
task3_pcb_pointer:	.space 60

cur_task:	.word 1
