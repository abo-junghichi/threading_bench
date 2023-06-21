#define DELAY (8)
#define NEXT(name) { void *label = decoded[dip]; decoded[dip] = labels[*ip++]; dip = (dip + 1) % DELAY; asm("##" #name); goto *label; } while (0)
#define guard(n) asm("#" #n)
main()
{
    /* this has 50% mispredictions (50-60% is typical in large benchmarks) */
    static void *labels[] =
	{ &&next1, &&next2, &&next3, &&next4, &&next5, &&loop, &&end };
    static char prog[] = { 0, 5, 1, 0, 2, 0, 3, 0, 4, 0, 6 };
    void *decoded[DELAY];
    int dip = 0;
    char *ip = prog + 1 + DELAY;
    int i = 0;
    int count = 100000000;
    for (i = 0; i < DELAY; i++)
	decoded[i] = labels[prog[i + 1]];
    i=0;
    goto *labels[prog[0]];
  next1:
    guard(1);
    NEXT(1);
  next2:
    guard(2);
    NEXT(2);
  next3:
    guard(3);
    NEXT(3);
  next4:
    guard(4);
    NEXT(4);
  next5:
    guard(5);
    NEXT(5);
  loop:
    if (count > 0) {
	count--;
	ip = prog;
    }
    NEXT(loop);
  end:
    //printf("%i\n", i);
    exit(0);
}
