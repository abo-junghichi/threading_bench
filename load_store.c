void dummy(void)
{
#define DEF(n) ".next" #n ":\n" "#" #n "\n" "incl var_k\n" "ret\n"
    asm volatile (DEF(1) DEF(2) DEF(3) DEF(4) DEF(5) ".loop:\n"
		  "mov var_k,%eax\n" "cmp $100000000,%eax\n"
		  "jg .L_loop_end\n" "add $1,var_k\n" "ret\n"
		  ".L_loop_end:\n" "mov $1,%ecx\n" "ret\n");
}
int main(void)
{
    static int volatile k asm("var_k") = 0;
    register int s asm("%ecx") = 0;
#define CALL(n) "call .next" #n "\n"
  start:
    asm volatile (CALL(1) CALL(2) CALL(1) CALL(3) CALL(1) CALL(4) CALL(1)
		  CALL(5) CALL(1) "call .loop\n":"=r"(s):"0"(s));
    if (0 == s)
	goto start;
    return 0;
}
