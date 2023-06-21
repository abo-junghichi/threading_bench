int main(void)
{
    static char prog[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5 };
    char *ip = prog;
    int count = 100000000;
#define JMP "movzbl (%0),%%eax\n" "addl $1,%0\n" "sall $4,%%eax\n" "addl %%ebx,%%eax\n" "jmp *%%eax\n"
//#define JMP "movzbl (%0),%%eax\n" "leal (%%ebx,%%eax,8),%%eax\n" "jmp *%%eax\n"
#define DEF(n) ".org table+16*" #n "\n" "table" #n ":\n"
#define DUMMY(n) DEF(n) JMP
    asm volatile ("table_start:\n" "movl $table,%%ebx\n" JMP ".p2align 4\n"
		  "table:\n" DUMMY(0) DUMMY(1) DUMMY(2) DUMMY(3) DUMMY(4)
		  DEF(5) "testl %1,%1\n" "jle 0f\n" "subl $1,%1\n"
		  "movl %2,%0\n" JMP "0:\n":"+&r"(ip),
		  "+&r"(count):"r"(prog):"eax", "ebx");
    return 0;
}
