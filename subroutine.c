void dummy(void)
{
#define DEF(n) ".p2align 5\n" ".next" #n ":\n" "#" #n "\n" "ret\n"
    asm volatile (DEF(1) DEF(2) DEF(3) DEF(4) DEF(5) ".p2align 5\n"
		  ".loop:\n" "cmp $100000000,%eax\n" "jg .L_loop_end\n"
		  "add $1,%eax\n" "ret\n" ".p2align 5\n" ".L_loop_end:\n"
		  "mov $1,%ecx\n" "ret\n");
}
int main(void)
{
    register int i asm("%eax") = 0, s asm("%ecx") = 0;
#define CALL(n) "call .next" #n "\n"
  start:
    asm volatile (CALL(1) CALL(2) CALL(1) CALL(3) CALL(1) CALL(4) CALL(1)
		  CALL(5) CALL(1) "call .loop\n":"=r"(i), "=r"(s):"0"(i),
		  "1"(s));
    if (0 == s)
	goto start;
    return 0;
}
