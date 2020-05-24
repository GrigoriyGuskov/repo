typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned short int Adress;
#define MEMSIZE (64*1024)

typedef struct {
	word val;		//занчение аргумента
	word adr;		//адрес аргумента
} Arg;

typedef struct {
	word mask;
	word opcode;
	byte par;		// B DD NN R SS XX
	char* name;
	void (* do_func)(void);
} Command;

#define	NO 0
#define haveXX 1
#define haveSS 2
#define haveR  4
#define haveNN 8
#define haveDD 16
#define haveB  32




byte mem[MEMSIZE];

word reg[8];

#define pc reg[7]
#define sp reg[6]

extern Command cmd[];

Arg ss, dd;

byte NN, R, B;
char XX;

byte N, Z, V, C;

void print_NZVC();

void set_NZ(word w);

byte b_read  (Adress adr);				// читает из "старой памяти" mem байт с "адресом" a.
void b_write (Adress adr, byte b);				// пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read  (Adress adr);
void w_write (Adress adr, word w);
void load_file();

void run();
void do_halt();
void do_mov ();
void do_add ();
void do_nothing ();
void do_sob ();
void do_br ();
void do_beq();
void do_bne();
void do_bmi();
void do_bpl();
void do_blt();
void do_bge();
void do_ble();
void do_clr();
void do_sub();
void do_jsr();
void do_rts();
void do_tst();
void do_cmp();
void do_ccc();
void do_clc();
void do_cln();
void do_clv();
void do_clz();
void do_scc();
void do_sec();
void do_sen();
void do_sev();
void do_sez();



Arg get_mr(word w);

byte get_R(word w);
byte get_NN(word w);
char get_XX(word w);
byte get_B(word w);
