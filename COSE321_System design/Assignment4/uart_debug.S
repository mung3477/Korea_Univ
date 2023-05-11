// ------------------------------------------
//  Author: Prof. Taeweon Suh
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   April 27, 2020
// ------------------------------------------

#include "uart_regs.h"

.macro UART_debug

// function label tabel
// 1: print str "at" r9
// 2: print char in r9
// 3: print hex in r10

		// --------  Store all register / cpsr values in stack --------------------------

	// ------------- Push order: lr -> cpsr -> pc -> sp -> r0 ~ r12 --------------
	// use r14 as temp register
	push {r14}				// store LR
	mrs r14, CPSR
	push {r14}				// store CPSR
	mov r14, r15			// r15 == PC
	sub r14, r14, #20		// restore initial PC value (before running the macro)
	push {r14}				// store initial PC in the stack
	mov r14, r13			// r13 == SP
	add r14, r14, #12		// restore initial SP value (before decrement 3 times)
	push {r14}				// store initial SP in the stack
	push {r0-r12}			// store other left registers

	.ltorg
	ldr	r9, =9f
	bl 1f	//	print ------

	ldr r9, =10f
	bl 1f	//	print r0: 0x
	add r0, SP, #0	// stacked r0 location
	ldr r10, [r0]			// load stacked r0 value
	bl 3f	// print hex

	ldr r9, =11f
	bl 1f	//	print r1: 0x
	add r0, SP, #4	// stacked r1 location
	ldr r10, [r0]			// load stacked r1 value
	bl 3f	// print hex

	ldr r9, =12f
	bl 1f	//	print r2: 0x
	add r0, SP, #8	// stacked r2 location
	ldr r10, [r0]			// load stacked r2 value
	bl 3f	// print hex

	ldr r9, =13f
	bl 1f	//	print r3: 0x
	add r0, SP, #12	// stacked r3 location
	ldr r10, [r0]			// load stacked r3 value
	bl 3f	// print hex

	ldr r9, =14f
	bl 1f	//	print r4: 0x
	add r0, SP, #16	// stacked r4 location
	ldr r10, [r0]			// load stacked r4 value
	bl 3f	// print hex

	ldr r9, =15f
	bl 1f	//	print r5: 0x
	add r0, SP, #20	// stacked r5 location
	ldr r10, [r0]			// load stacked r5 value
	bl 3f	// print hex

	ldr r9, =16f
	bl 1f	//	print r6: 0x
	add r0, SP, #24	// stacked r6 location
	ldr r10, [r0]			// load stacked r6 value
	bl 3f	// print hex

	ldr r9, =17f
	bl 1f	//	print r7: 0x
	add r0, SP, #28	// stacked r7 location
	ldr r10, [r0]			// load stacked r7 value
	bl 3f	// print hex

	ldr r9, =18f
	bl 1f	//	print r8: 0x
	add r0, SP, #32	// stacked r8 location
	ldr r10, [r0]			// load stacked r8 value
	bl 3f	// print hex

	ldr r9, =19f
	bl 1f	//	print r9: 0x
	add r0, SP, #36	// stacked r9 location
	ldr r10, [r0]			// load stacked r9 value
	bl 3f	// print hex

	ldr r9, =20f
	bl 1f	//	print r10: 0x
	add r0, SP, #40	// stacked r10 location
	ldr r10, [r0]			// load stacked r10 value
	bl 3f	// print hex

	ldr r9, =21f
	bl 1f	//	print r11: 0x
	add r0, SP, #44	// stacked r11 location
	ldr r10, [r0]			// load stacked r11 value
	bl 3f	// print hex

	ldr r9, =22f
	bl 1f	//	print r12: 0x
	add r0, SP, #48	// stacked r12 location
	ldr r10, [r0]			// load stacked r12 value
	bl 3f	// print hex

	ldr r9, =23f
	bl 1f	//	print r13: 0x
	add r0, SP, #52	// stacked r13 location
	ldr r10, [r0]			// load stacked r13 value
	bl 3f	// print hex

	ldr r9, =24f
	bl 1f	//	print r14: 0x
	add r0, SP, #64	// stacked r14 location
	ldr r10, [r0]			// load stacked r14 value
	bl 3f	// print hex

	ldr r9, =25f
	bl 1f	//	print r15: 0x
	add r0, SP, #56	// stacked r15 location
	ldr r10, [r0]			// load stacked r15 value
	bl 3f	// print hex

	ldr r9, =26f
	bl 1f	//	print cpsr:
	add r0, SP, #60	// stacked cpsr location
	ldr r10, [r0]			// load stacked cpsr value

	ldr r8, =(1 << 31)
	and r0, r10, r8
	cmp r0, #0
	ldreq r9, =#110			// n
	ldrne r9, =#78			// N
	bl 2f					// print char

	lsr r8, #1
	and r0, r10, r8
	cmp r0, #0
	ldreq r9, =#122			// z
	ldrne r9, =#90			// Z
	bl 2f					// print char

	lsr r8, #1
	and r0, r10, r8
	cmp r0, #0
	ldreq r9, =#99			// c
	ldrne r9, =#67			// C
	bl 2f					// print char

	lsr r8, #1
	and r0, r10, r8
	cmp r0, #0
	ldreq r9, =#118			// v
	ldrne r9, =#86			// V
	bl 2f					// print char

	ldr r12, =#0x01000020
	and r8, r10, r12

	ldr r9, =42f
	and r0, r10, #0x0000F000
	lsr r0, r0, #12
	cmp r0, #0
	ldreq r9, =27f
	cmp r0, #1
	ldreq r9, =28f
	cmp r0, #2
	ldreq r9, =29f
	cmp r0, #3
	ldreq r9, =30f
	cmp r0, #4
	ldreq r9, =31f
	cmp r0, #5
	ldreq r9, =32f
	cmp r0, #6
	ldreq r9, =33f
	cmp r0, #7
	ldreq r9, =34f
	cmp r0, #8
	ldreq r9, =35f
	cmp r0, #9
	ldreq r9, =36f
	cmp r0, #10
	ldreq r9, =37f
	cmp r0, #11
	ldreq r9, =38f
	cmp r0, #12
	ldreq r9, =39f
	cmp r0, #13
	ldreq r9, =40f
	cmp r0, #14
	ldreq r9, =41f

	cmp r8, #0
	ldreq r9, =42f
	bleq 1f
	ldreq r9, =43f
	bleq 1f	// print ", IF, ARM mode"

	cmp r8, #0x00000020
	bleq 1f
	ldreq r9, =44f
	bleq 1f	// print ", IF ..., Thumb2 mode"

	cmp r8, #0x01000000
	ldreq r9, =42f
	bleq 1f
	ldreq r9, =45f
	bleq 1f	// print ", IF, Jazelle mode"

	cmp r8, r12	// 0x01000020
	bleq 1f
	ldreq r9, =46f
	bleq 1f	// print ", IF ..., ThumbEE mode"

	and r0, r10, #0x0000001F
	ldr r9, =#0
	cmp r0, #16
	ldreq r9, =47f
	cmp r0, #17
	ldreq r9, =48f
	cmp r0, #18
	ldreq r9, =49f
	cmp r0, #19
	ldreq r9, =50f
	cmp r0, #22
	ldreq r9, =51f
	cmp r0, #23
	ldreq r9, =52f
	cmp r0, #26
	ldreq r9, =53f
	cmp r0, #27
	ldreq r9, =54f
	cmp r0, #31
	ldreq r9, =55f
	cmp r9, #0
	blne 1f	// print "current mode: ... "

	ldr r9, =56f
	bl 1f	// print "( =0x"
	bl 3f	// print hex

	ldr r9, =57f
	bl 1f	//print end line
	b 7f	// end

//print_str: print string in r9
1:
	// --------- Check to see if the Tx FIFO is empty ------------------------------
	ldr	r0, =uart_Channel_sts_reg0
	ldr r2, [r0]		// read Channel Status Register
	and	r2, r2, #0x8	// read Transmit Buffer Empty bit(bit[3])
	cmp	r2, #0x8		// check if TxFIFO is empty and ready to receive new data
	bne	1b				// if TxFIFO is NOT empty, keep checking until it is empty
	//------------------------------------------------------------------------------

	push {LR}
	ldrb r3, [r9], #1
	ldr  r1, =uart_TX_RX_FIFO0
	strb r3, [r1]	// fill the TxFIFO with r9
	cmp  r3, #0x00
	popne {LR}
	bne  1b
	pop {LR}
	mov PC, LR

//print_char: print a byte in r9
2:
	// --------- Check to see if the Tx FIFO is empty ------------------------------
	ldr	r0, =uart_Channel_sts_reg0
	ldr r2, [r0]		// read Channel Status Register
	and	r2, r2, #0x8	// read Transmit Buffer Empty bit(bit[3])
	cmp	r2, #0x8		// check if TxFIFO is empty and ready to receive new data
	bne	2b				// if TxFIFO is NOT empty, keep checking until it is empty
	//------------------------------------------------------------------------------

	push {LR}
	ldr  r1, =uart_TX_RX_FIFO0
	strb r9, [r1]	// fill the TxFIFO with r9
	pop {LR}
	mov PC, LR

// print hex, uses r10
3:
	push {LR}
	ldr	r3, =(1 << 31)	// first bit
	ldr r4, =#8			// loop count

// 4bit_to_char_loop:
31:
	and r2, r10, r3			// bitmask first bit
	lsr r3, #1
	and r0, r10, r3			// bitmask second bit
	orr r2, r0, r2			// concat the result with r2
	lsr r3, #1
	and r0, r10, r3			// bitmask third bit
	orr r2, r0, r2			// concat the result with r2
	lsr r3, #1
	and r0, r10, r3			// bitmask fourth bit
	orr r2, r0, r2			// concat the result with r2. Now r2 has 4 bit's hex value
	lsr r3, #1

	sub r4, r4, #1			// decrease loop count
	lsl	r0, r4, #2
	lsr r2, r2, r0			// delete tailing zeros of r2
	ldr r12, =8f				// hex string
	add r2, r12, r2			// r2 is offset
	ldrb r9, [r2]			// hex to char using r2 as an index of string. hex_str[r2]
	bl	2b					// print char

	cmp r4, #4
	ldreq r9, =#95
	bleq	2b					// print '_'
	cmp r4, #0
	bne 31b	// loop until we see all bits

	pop {LR}
	mov PC, LR

//	----------- Reroll register values --------------
7:
	pop {r0-r12}
	pop {lr}				// SP
	pop {lr}				// PC
	pop {lr}				// CPSR
	msr cpsr, lr			// restore cpsr
	pop {lr}				// LR

	.data
8:
	.ascii "0123456789abcdef"
9:
	.ascii "-----------------------------------------------------------------------------------------------------"
	.byte 0x00
10:
	.byte 0x0D
	.byte 0x0A
	.ascii "r0  = 0x"
	.byte 0x00
11:
	.ascii ", r1 = 0x"
	.byte 0x00
12:
	.ascii ",  r2  = 0x"
	.byte 0x00
13:
	.ascii ", r3 = 0x"
	.byte 0x00
14:
	.byte 0x0D
	.byte 0x0A
	.ascii "r4  = 0x"
	.byte 0x00
15:
	.ascii ",   r5 = 0x"
	.byte 0x00
16:
	.ascii ",  r6  = 0x"
	.byte 0x00
17:
	.ascii ", r7 = 0x"
	.byte 0x00
18:
	.byte 0x0D
	.byte 0x0A
	.ascii "r8  = 0x"
	.byte 0x00
19:
	.ascii ", r9 = 0x"
	.byte 0x00
20:
	.ascii ",  r10 = 0x"
	.byte 0x00
21:
	.ascii ", r11 = 0x"
	.byte 0x00
22:
	.byte 0x0D
	.byte 0x0A
	.ascii "r12 = 0x"
	.byte 0x00
23:
	.ascii ", r13 = 0x"
	.byte 0x00
24:
	.ascii ", r14 = 0x"
	.byte 0x00
25:
	.ascii ", r15 = 0x"
	.byte 0x00
26:
	.byte 0x0D
	.byte 0x0A
	.ascii "cpsr = "
	.byte 0x00
27:
	.ascii ", IF EQ, "
	.byte 0x00
28:
	.ascii ", IF NE, "
	.byte 0x00
29:
	.ascii ", IF CS, "
	.byte 0x00
30:
	.ascii ", IF CC, "
	.byte 0x00
31:
	.ascii ", IF MI, "
	.byte 0x00
32:
	.ascii ", IF PL, "
	.byte 0x00
33:
	.ascii ", IF VS, "
	.byte 0x00
34:
	.ascii ", IF VC, "
	.byte 0x00
35:
	.ascii ", IF HI, "
	.byte 0x00
36:
	.ascii ", IF LS, "
	.byte 0x00
37:
	.ascii ", IF GE, "
	.byte 0x00
38:
	.ascii ", IF LT, "
	.byte 0x00
39:
	.ascii ", IF GT, "
	.byte 0x00
40:
	.ascii ", IF LE, "
	.byte 0x00
41:
	.ascii ", IF AL, "
	.byte 0x00
42:
	.ascii ", IF, "
	.byte 0x00
43:
	.ascii "ARM mode, "
	.byte 0x00
44:
	.ascii "Thumb2 mode, "
	.byte 0x00
45:
	.ascii "Jazelle mode, "
	.byte 0x00
46:
	.ascii "ThumbEE mode, "
	.byte 0x00
47:
	.ascii "current mode = USR "
	.byte 0x00
48:
	.ascii "current mode = FIQ "
	.byte 0x00
49:
	.ascii "current mode = IRQ "
	.byte 0x00
50:
	.ascii "current mode = SVC "
	.byte 0x00
51:
	.ascii "current mode = MON "
	.byte 0x00
52:
	.ascii "current mode = ABT "
	.byte 0x00
53:
	.ascii "current mode = HYP "
	.byte 0x00
54:
	.ascii "current mode = UND "
	.byte 0x00
55:
	.ascii "current mode = SYS "
	.byte 0x00
56:
	.ascii "( =0x"
	.byte 0x00
57:
	.byte 0x29
	.byte 0x0D
	.byte 0x0A
	.ascii "-----------------------------------------------------------------------------------------------------"
	.byte 0x0D
	.byte 0x0A
	.byte 0x00
.text
.endm
