#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"




Arg get_mr(word w) {
	Arg res;
	int r = w & 7;				//номер регистра
	int mode = (w >> 3) & 7;	//номeр моды
	switch(mode){
		case 0:					//R3
			res.adr = r;
			res.val = reg[r];
			printf("R%o ",r);
			break;
		case 1:					//(R3)
			res.adr = reg[r];
			if (B)
				res.val = b_read(res.adr);
			else
				res.val = w_read(res.adr);
			printf("(R%o) ",r);
			break;
		case 2:					//#3
			res.adr = reg[r];
			if (B){
				res.val = b_read(res.adr);
				if(r<6)
					reg[r]++;
				else
					reg[r] += 2;
			}
			else {
				res.val = w_read(res.adr);
				reg[r] += 2;
			}
			if (r == 7)
				printf("#%o ",res.val);
			else
				printf("(R%o)+ ",r);
			break;
		case 3:
			res.adr = w_read(reg[r]);
			if(B) {
				res.val = b_read(res.adr);
				reg[r] ++;
			}
			else {
				res.val = w_read(res.adr);
				reg[r] += 2;
			} 
			if (r == 7)
				printf("@#%o ",res.adr);
			else
				printf("@(R%o)+ ",r);
			break;
		case 4:					
			if(B) {
				if(r<6)
					reg[r]--;
				else
					reg[r] -= 2;
				res.adr = reg[r];
				res.val = w_read(res.adr);
			}
			else {
				reg[r] -= 2;
				res.adr = reg[r];
				res.val = w_read(res.adr);
			}
			printf("-(R%o) ",r);
			break;
		default:
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
			exit(1);
	}
	return res;
}

byte get_R(word w) {
	byte res;
	res = (w>>6) & 7;
	printf("R%o ", res);
	return res;
}

byte get_B(word w) {
	byte res;
	res = (w >> 15) & 1;
	return res;
}

byte get_NN(word w) {
	printf("%o ", w & 63);
	return w & 63;
}

char get_XX(word w) {
	printf("%o ", w & 255);
	return w & 255;
}

void run() {
	pc = 01000;
	load_file();
	while(1) {
		word w = w_read(pc);
		printf("\n%06o %06o: ", pc, w);
		pc += 2;
		
		/*if (w == 0) {
			printf("HALT ");
			do_halt();
		}*/
		//else {
			for(int i = 0; cmd[i].mask ; i++){
				if((w & cmd[i].mask) == cmd[i].opcode) {
					printf("%s ", cmd[i].name);
					if(cmd[i].par & 32)
						B = get_B(w);
					if(cmd[i].par & 1)
						XX = get_XX(w);
					if(cmd[i].par & 2)
						ss = get_mr(w >> 6);
					if(cmd[i].par & 4)
						R = get_R(w);
					if(cmd[i].par & 8)
						NN = get_NN(w); 
					if(cmd[i].par & 16)
						dd = get_mr(w);
					cmd[i].do_func();
				}
			}
		//}
		
		
		/*
		if (w == 0) {
			printf("halt ");
			do_halt();
		}
		else if ((w & 0170000) == 0010000) {
			printf("mov ");
			ss = get_mr(w >> 6);
			dd = get_mr(w);
			do_mov ();
		}
		else if ((w & 0170000) == 0060000) {
			printf("add ");
			ss = get_mr(w >> 6);
			dd = get_mr(w);
			do_add ();
		}
		else if ((w & 0177000) == 0077000) {
			printf("sob ");
			R = get_R(w);
			NN = get_NN(w);
			do_sob ();
		}
		else if ((w & 0xff00) == 0x0100) {
			printf("br ");
			XX = get_XX(w);
			do_br ();
		}
		else 
			do_nothing ();*/
		printf("\n");
		for(int i = 0; i<8; i++)
			printf("R%o=%o ", i, reg[i]);
		print_NZVC();
	}
}

