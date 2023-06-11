// ------------------------------------------
//  Author: Prof. Taeweon Suh
//          Computer Science & Engineering
//          College of Informatics, Korea Univ.
//  Date:   June 01, 2022
//
//  It is based on Boot code in Xilinx SDK
// ------------------------------------------

.globl  csd_MMUTable_fig1
.globl  csd_MMUTable_fig2
.section .csd_mmu_tbl,"a"
csd_MMUTable_fig1:
	/* A 32-bit is required for each PTE (Page Table Entry).
	 * Each PTE covers a 1MB section.
	 * There are 4096 PTEs, so 16KB is required for the page table.
	 *
	 *  First 6 PTEs with the following translations
	 *     1st 1MB: 0x0000_0000 (VA) -> 0x0000_0000 (PA)
	 *     2nd 1MB: 0x0010_0000 (VA) -> 0x0010_0000 (PA)
	 *     3rd 1MB: 0x0020_0000 (VA) -> lv2 page table
	 */
.set SECT, 0
.word	SECT + 0x15de6		/* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */
.set	SECT, SECT + 0x100000
.word	SECT + 0x15de6		/* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */
.set	SECT, SECT + 0x100000
.word	csd_MMUTable_lv2_fig1 + 0x1e1 /* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */

.align 14
csd_MMUTable_fig2:
	/* A 32-bit is required for each PTE (Page Table Entry).
	 * Each PTE covers a 1MB section.
	 * There are 4096 PTEs, so 16KB is required for the page table.
	 *
	 *  First 6 PTEs with the following translations
	 *     1st 1MB: 0x0000_0000 (VA) -> 0x0000_0000 (PA)
	 *     2nd 1MB: 0x0010_0000 (VA) -> 0x0010_0000 (PA)
	 *     3rd 1MB: 0x0020_0000 (VA) -> lv2 page table
	 */
.set SECT, 0
.word	SECT + 0x15de6		/* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */
.set	SECT, SECT + 0x100000
.word	SECT + 0x15de6		/* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */
.set	SECT, SECT + 0x100000
.word	csd_MMUTable_lv2_fig2 + 0x1e1 /* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */


.section .csd_mmu_tbl_lv2,"a"
// 2nd level page table
.align 10
csd_MMUTable_lv2_fig1:
	/*
	* A 32-bit is required for each PTE
	* Each PTE covers 4KB section.
	* First 4 PTEs with following transitions
	*	1st 4KB: 0x0020_0000 (VA) -> 0x0040_0000 (PA)
	*	2nd 4KB: 0x0020_1000 (VA) -> 0x0040_1000 (PA)
	*	3rd 4KB: 0x0020_2000 (VA) -> 0x0040_2000 (PA)
	*/

.set SECT2, 0x400000
.word SECT2 + 0x576 /* S=b1 TEX=b101 AP=b11, C=b0, B=b1 */
.set SECT2, SECT2 + 0x1000
.word SECT2 + 0x576
.set SECT2, SECT2 + 0x1000
.word SECT2 + 0x576

.align 10
csd_MMUTable_lv2_fig2:

	//	1st 4KB: 0x0020_0000 (VA) -> 0x0040_0000 (PA)
	//	2nd 4KB: 0x0020_1000 (VA) -> 0x0040_0000 (PA)
	//	3rd 4KB: 0x0020_2000 (VA) -> 0x0040_2000 (PA)

.set SECT2, 0x400000
.word SECT2 + 0x576
.word SECT2 + 0x576
.set SECT2, SECT2 + 0x2000
.word SECT2 + 0x576

.end
