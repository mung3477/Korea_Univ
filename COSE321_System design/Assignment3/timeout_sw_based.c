#define csd_SW_ADDR 0x41210000

/**
	in while statement, sub and compare are implemented in 6 arm instructions.
	  1006a4:	e51b3008 	ldr	r3, [fp, #-8]
	  1006a8:	e2433001 	sub	r3, r3, #1	
	  1006ac:	e50b3008 	str	r3, [fp, #-8]
		while (t) 
	  1006b0:	e51b3008 	ldr	r3, [fp, #-8]	
	  1006b4:	e3530000 	cmp	r3, #0		
	  1006b8:	1afffff9 	bne	1006a4 <setTimeout+0x14>
  	
  	Assume this loop costs 20 clocks. (This was based on experiment, by adapting the weight of t below)
  	
	  	ldr r2, =#3,000,000,000
	calc_clk:
		subs r2, r2, #1
		bne calc_clk
		nop
  	
  	According to my experiment using the code above, clock frequency was 2GHz.
  	This means each clock is consisted of 0.5ns.
  	Approximately each loop consumes 10ns.
  	
  	To make this function consume tms (t * 1,000,000ns), we use 100,000 * t in while statement. 
 */
void setTimeout(unsigned int t) {
	t *= 100000;
	while (t) 
		t -= 1;
	return;
}

void timeout_sw_based() {
	unsigned char * SW = (unsigned char *)csd_SW_ADDR;
	unsigned int sw_status = *SW;
	unsigned int time = 100;
	
	if (sw_status == 0) {
		setTimeout(1000);
		return;
	}
	// setTimeout 100ms * N based on given conditions in assignment documentation
	while (sw_status < 256) {
		sw_status = sw_status << 1;
		time += 100;
	}
	setTimeout(time);
	return;
}
