#define BEGIN { void *wwip = wip
#define FETCH wip = *ip++
#define NEXT goto *wwip; } while (0)
#define guard(n) asm("#" #n)
main()
{
    /* this has 50% mispredictions (50-60% is typical in large benchmarks) */
    static void *labels[] =
	{ &&next1, &&next2, &&next3, &&next4, &&next5, &&loop };
    static void *prog[] =
	{ &&next1, &&next2, &&next1, &&next3, &&next1, &&next4, &&next1,
&&next5, &&loop, &&next1 };
    void *wip = prog[1];
    void **ip = prog + 2;
    int i = 0;
    int count = 100000000;
    goto *prog[0];
  next1:
    BEGIN;
    FETCH;
    guard(1);
    NEXT;
  next2:
    BEGIN;
    FETCH;
    guard(2);
    NEXT;
  next3:
    BEGIN;
    FETCH;
    guard(3);
    NEXT;
  next4:
    BEGIN;
    FETCH;
    guard(4);
    NEXT;
  next5:
    BEGIN;
    FETCH;
    guard(5);
    NEXT;
  loop:
    BEGIN;
    if (count > 0) {
	count--;
	ip = prog;
	FETCH;
    } else
	exit(0);
    NEXT;
}
