#define ALIGN (3)
#define NEXT goto *((((unsigned long)*ip++) << ALIGN) + &&loop)
#define guard(n) asm("#" #n)
main()
{
    /* this has 50% mispredictions (50-60% is typical in large benchmarks) */
    static void *prog_src[] =
	{ &&next1, &&next2, &&next1, &&next3, &&next1, &&next4, &&next1,
	&&next5, &&next1, &&loop
    };
    char prog[10];
    char *ip = prog;
    int i;
    int count = 100000000;
    for (i = 0; i < 10; i++) {
	unsigned long direct = prog_src[i] - &&loop, rst = direct >> ALIGN;
	if (direct != rst << ALIGN)
	    exit(0);
	prog[i] = rst;
    }
    NEXT;
  next1:
    guard(1);
    NEXT;
  next2:
    guard(2);
    NEXT;
  next3:
    guard(3);
    NEXT;
  next4:
    guard(4);
    NEXT;
  next5:
    guard(5);
    NEXT;
  loop:
    if (count > 0) {
	count--;
	ip = prog;
	NEXT;
    }
    exit(0);
}
