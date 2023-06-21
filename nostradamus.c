#include <stdlib.h>
typedef void **(*Inst) (void);
#define guard(n) asm("#" #n)
extern Inst prog[];
#define next(n) \
void** next##n(void)\
{\
  guard(n);\
  return NULL;\
}
next(1);
next(2);
next(3);
next(4);
next(5);
void **loop(void)
{
    static int count = 100000000;
    if (count <= 0)
	exit(0);
    count--;
    return prog;
}
Inst prog[] = {
    next1, next2, next1, next3, next1, next4, next1, next5, next1, loop
};
int main(void)
{
    Inst *ip = prog;
    while (1) {
	Inst *jip;
#define DISPATCH \
	jip = (*(ip++)) ();\
	if (NULL != jip)\
	    goto drop
	DISPATCH;
	DISPATCH;
	DISPATCH;
	DISPATCH;
	DISPATCH;
	DISPATCH;
	DISPATCH;
	DISPATCH;
	continue;
      drop:ip = jip;
    }
}
