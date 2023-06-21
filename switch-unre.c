#define NEXT break
#define guard(n) asm("#" #n)
typedef struct {
    unsigned int n:3;
} inst;
main()
{
    static inst prog[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5 };
    inst *ip = prog;
    int count = 100000000;
    for (;;) {
	switch ((ip++)->n) {
	case 0:
	    guard(0);
	    NEXT;
	case 1:
	    guard(1);
	    NEXT;
	case 2:
	    guard(2);
	    NEXT;
	case 3:
	    guard(3);
	    NEXT;
	case 4:
	    guard(4);
	    NEXT;
	case 5:
	case 6:
	case 7:
	    if (count > 0) {
		count--;
		ip = prog;
		NEXT;
		/* the rest is to get gcc to make a realistic switch statement */
	    } else
		exit(0);
	default:
	    __builtin_unreachable();
	}
    }
}
