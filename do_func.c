#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"


Command cmd[] = {
		{0177777, 0000240, NO, "NOP", do_nothing},

		{0177777, 0000257, NO, "CCC", do_ccc},
		{0177777, 0000241, NO, "CLC", do_clc},
		{0177777, 0000250, NO, "CLN", do_cln},
		{0177777, 0000242, NO, "CLV", do_clv},
		{0177777, 0000244, NO, "CLZ", do_clz},

		{0177777, 0000277, NO, "SCC", do_scc},
		{0177777, 0000261, NO, "SEC", do_sec},
		{0177777, 0000270, NO, "SEN", do_sen},
		{0177777, 0000262, NO, "SEV", do_sev},
		{0177777, 0000264, NO, "SEZ", do_sez},

		//{0177770, 0000200, NO, "RTS", do_rts},

		{0177400, 0000400, haveXX, "BR", do_br},
		{0177400, 0001400, haveXX, "BEQ", do_beq},
		{0177400, 0001000, haveXX, "BNE", do_bne},
		{0177400, 0100400, haveXX, "BMI", do_bmi},
		{0177400, 0100000, haveXX, "BPL", do_bpl},
		/*{0177400, 0002400, haveXX, "BLT", do_blt},
		{0177400, 0002000, haveXX, "BGE", do_bge},
		{0177400, 0003400, haveXX, "BLE", do_ble},
*/
		{0177000, 0077000, haveR | haveNN, "SOB", do_sob},
	//	{0177000, 0004000, haveR | haveDD, "JSR", do_jsr},

		{0170000, 0060000, haveSS | haveDD, "ADD", do_add},
	//	{0170000, 0160000, haveSS | haveDD, "SUB", do_sub},

	//	{0077700, 0005000, haveB | haveDD, "CLR", do_clr},
	//	{0077700, 0005700, haveB | haveDD, "TST", do_tst},

		{0070000, 0010000, haveB | haveSS | haveDD, "MOV", do_mov},
	//	{0070000, 0020000, haveB | haveSS | haveDD, "CMP", do_cmp},
		
		{0177777, 0000000, NO, "HALT", do_halt},
		
		{0, 0, NO, "empty command", do_nothing},
	};


void set_NZ (word w) {
	if(w == 0){
		N = 0;
		Z = 1;
	}
	else {
		Z = 0;
		if(get_B(w))
			N = (w >> 15) & 1;
		else
			N = (w >> 7) & 1;
	}
}
void set_C(word w);

void print_NZVC(){
	printf("\n N=%o Z=%o V=%o C=%o ",N ,Z ,V ,C);
}

void do_halt() {
	printf("THE END!!!\n");
	exit(0);
}

void do_mov () {
	if(B)
		b_write(dd.adr, ss.val); 
	else
		w_write(dd.adr, ss.val);
	set_NZ (ss.val);
	B = 0;
}

void do_add () {
	w_write(dd.adr, ss.val + dd.val);
	set_NZ (ss.val + dd.val);
	C = ((ss.val + dd.val) >> (8 * sizeof(word))) & 1;
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

void do_beq() {
    if(Z)
        do_br();
}

void do_bne() {
    if(!Z)
        do_br();
}

void do_bmi() {
    if(N)
        do_br	();
}

void do_bpl() {
    if(!N)
        do_br();
}

void do_ccc()
{
	N = 0;
	Z =0;
	V = 0;
	C = 0;
}

void do_clc()
{
    C = 0;
}

void do_cln()
{
    N = 0;
}

void do_clv()
{
	V = 0;
}

void do_clz()
{
    Z = 0;
}


void do_scc()
{
    N = 1;
	Z = 1;
	V = 1;
	C = 1;
}

void do_sec()
{
    C = 1;
}

void do_sen()
{
    N = 1;
}

void do_sev()
{
    V = 1;
}

void do_sez()
{
    Z = 1;
}



void do_nothing () {}