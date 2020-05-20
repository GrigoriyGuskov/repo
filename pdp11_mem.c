#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "pdp.h"

/*typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;
#define MEMSIZE (64*1024)


byte mem[MEMSIZE];

word reg[8];
#define pc reg[7]

byte b_read  (Adress adr);				// читает из "старой памяти" mem байт с "адресом" a.
void b_write (Adress adr, byte b);				// пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read  (Adress adr);
void w_write (Adress adr, word w);*/

void test_mem() {
	byte b0 = 0x0a;
	b_write(2,b0);
	byte bres = b_read(2);
	printf("%02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);
	
	Adress a = 4;
	byte b1 = 0x0b;
	word w = 0x0b0a;
	w_write(a,w);
	word wres = w_read (a);
	printf("%04hx=%02hhx%02hhx\n", wres, b1, b0);
	assert(w == wres);
}

int main() {
	//test_mem();
	run();
	return 0;
}

byte b_read  (Adress adr) {
    return mem[adr];
}

void b_write (Adress adr, byte b) {
    mem[adr] = b;
}

word w_read  (Adress adr) {
	word w = 0;
	w = ((word)mem[adr + 1]) << 8;
	w = w | mem[adr];
	return w;
}

void w_write (Adress adr, word w) {
	word t = w;
	mem[adr] = (byte)t;
	t = w;
	mem[adr + 1] = (byte) (t >> 8);
}

void load_file() {
    short int point = 0;
    short int n = 0;
    uint8_t current = 0;

    int z = 0;

    while((z = scanf("%hx", &point)) > 0) {
        //printf ("%d\n", z);
        z = scanf("%hx", &n);
        //printf ("%d\n", z);

        for (short int i = 0; i < n; i++) {
            scanf("%hhx", &current);
            b_write(point + i, current);
        }
    }
}