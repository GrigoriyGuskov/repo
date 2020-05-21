#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"



void do_halt() {
	printf("THE END!!!\n");
	exit(0);
}

void do_mov () {
	w_write(dd.adr, ss.val);
	reg[dd.adr] = ss.val;
}

void do_add () {
	w_write(dd.adr, ss.val + dd.val);
	reg[dd.adr] = ss.val + dd.val;
}

void do_sob () {
	if(reg[R]) {
		pc = pc - NN*2;
		reg[R]--;
	}
}

void do_br () {
	pc = pc + XX*2;

}

void do_nothing () {
	printf("unknown\n");
}


Command cmd[] = {
	{0170000, 0010000, "mov", do_mov},
	{0170000, 0060000, "add", do_add},
	{0177000, 0077000, "sob", do_sob},
	{0xff00, 0x0100, "br", do_br},
	
	{0, 0, "halt ", do_halt}
};