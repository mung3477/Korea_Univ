// ------------------------------------------
//  Author: Prof. Taeweon Suh
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   May 29, 2022
// ------------------------------------------

.global main
main:

	/* Disable MMU, if enabled */
	mrc	p15, 0, r0, c1, c0, 0		/* read CP15 register 1 */
	bic	r0, r0, #0x1			/* clear bit 0 */
	mcr	p15, 0, r0, c1, c0, 0		/* write value back */

	/* Invalidate caches and TLBs */
	mov	r0,#0				/* r0 = 0  */
	mcr	p15, 0, r0, c8, c7, 0		/* invalidate TLBs */
	mcr	p15, 0, r0, c7, c5, 0		/* invalidate icache */
	mcr	p15, 0, r0, c7, c5, 6		/* Invalidate branch predictor array */

	// Clear PD0 in TTBCR (Translation Table Base Control Register)
	mrc p15, 0, r2, c2, c0, 2
	bic r2, r2, #(1<<4)   // Set PD0 to 0 = HW-based page table walk
	mcr p15, 0, r2, c2, c0, 2

	/* Enable MMU */
	// Set M-bit in SCTLR (System Control Register)
	mrc	p15, 0, r0, c1, c0, 0
	bic r0, r0, #(1<<12)  // I-bit = I$ disable
	bic r0, r0, #(1<<2)   // C-bit = $ disable
	orr r0, r0, #(1<<0)   // M-bit = MMU enable
	mcr	p15, 0, r0, c1, c0, 0	/* Enable MMU */
	dsb					        /* dsb	allow the MMU to start up */
	isb					        /* isb	flush prefetch buffer */


	// start: initialize main memory
	ldr r0, =#0x400000
	ldr r1, =#-1024
	ldr r2, =#0x403000
	ldr r3, =#1

init_loop:
	cmp r0, r2
	bge init_break
	str r1, [r0]
	add r1, r1, r3
	cmp r1, #0
	addeq r1, r1, #1
	add r0, r0, r3, lsl #2
	b init_loop
	// end: initialize main memory

init_break:

	// =================== start: MMU fig1 ======================================
	/* Disable MMU, if enabled */
	mrc	p15, 0, r0, c1, c0, 0		/* read CP15 register 1 */
	bic	r0, r0, #0x1			/* clear bit 0 */
	mcr	p15, 0, r0, c1, c0, 0		/* write value back */

	/* Invalidate caches and TLBs */
	mov	r0,#0				/* r0 = 0  */
	mcr	p15, 0, r0, c8, c7, 0		/* invalidate TLBs */
	mcr	p15, 0, r0, c7, c5, 0		/* invalidate icache */
	mcr	p15, 0, r0, c7, c5, 6		/* Invalidate branch predictor array */

	ldr	r0,=csd_MMUTable_fig1	   /* Load MMU translation table base */
	orr	r0, r0, #0x5B			/* Outer-cacheable, WB */
	mcr	15, 0, r0, c2, c0, 0		/* TTBR0 */

	// Clear PD0 in TTBCR (Translation Table Base Control Register)
	mrc p15, 0, r2, c2, c0, 2
	bic r2, r2, #(1<<4)   // Set PD0 to 0 = HW-based page table walk
	mcr p15, 0, r2, c2, c0, 2

	/* Enable MMU */
	// Set M-bit in SCTLR (System Control Register)
	mrc	p15, 0, r0, c1, c0, 0
	bic r0, r0, #(1<<12)  // I-bit = I$ disable
	bic r0, r0, #(1<<2)   // C-bit = $ disable
	orr r0, r0, #(1<<0)   // M-bit = MMU enable
	mcr	p15, 0, r0, c1, c0, 0	/* Enable MMU */
	dsb					        /* dsb	allow the MMU to start up */
	isb					        /* isb	flush prefetch buffer */

	bl sum
	// =================== end: MMU fig1 ======================================

	// =================== start: MMU fig2 ======================================
	/* Disable MMU, if enabled */
	mrc	p15, 0, r0, c1, c0, 0		/* read CP15 register 1 */
	bic	r0, r0, #0x1			/* clear bit 0 */
	mcr	p15, 0, r0, c1, c0, 0		/* write value back */

	/* Invalidate caches and TLBs */
	mov	r0,#0				/* r0 = 0  */
	mcr	p15, 0, r0, c8, c7, 0		/* invalidate TLBs */
	mcr	p15, 0, r0, c7, c5, 0		/* invalidate icache */
	mcr	p15, 0, r0, c7, c5, 6		/* Invalidate branch predictor array */

	ldr	r0,=csd_MMUTable_fig2	   /* Load MMU translation table base */
	orr	r0, r0, #0x5B			/* Outer-cacheable, WB */
	mcr	15, 0, r0, c2, c0, 0		/* TTBR0 */

	// Clear PD0 in TTBCR (Translation Table Base Control Register)
	mrc p15, 0, r2, c2, c0, 2
	bic r2, r2, #(1<<4)   // Set PD0 to 0 = HW-based page table walk
	mcr p15, 0, r2, c2, c0, 2

	/* Enable MMU */
	// Set M-bit in SCTLR (System Control Register)
	mrc	p15, 0, r0, c1, c0, 0
	bic r0, r0, #(1<<12)  // I-bit = I$ disable
	bic r0, r0, #(1<<2)   // C-bit = $ disable
	orr r0, r0, #(1<<0)   // M-bit = MMU enable
	mcr	p15, 0, r0, c1, c0, 0	/* Enable MMU */
	dsb					        /* dsb	allow the MMU to start up */
	isb					        /* isb	flush prefetch buffer */

	bl sum
	// =================== start: MMU fig2 ======================================

forever:
	nop
	b forever

sum:
	// start: add all the integers in 12KB space from 0x20_0000 to 0x20_2FFF
	ldr r0, =#0x200000
	ldr r1, =#0
	ldr r2, =#0x203000

loop:
	cmp r0, r2
	bge break

   	ldr r3, [r0]
   	add r1, r1, r3
   	add r0, r0, #(1 << 2)
   	b loop

break:
	// end: add all the integers in 12KB range
	mov pc, lr
