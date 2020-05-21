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
	char* name;
	void (* do_func)(void);
} Command;

byte mem[MEMSIZE];

word reg[8];

#define pc reg[7]

Command cmd[];

Arg ss, dd;

byte NN, R;
char XX;

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

Arg get_mr(word w);

byte get_R(word w);
byte get_NN(word w);
byte get_XX(word w);
