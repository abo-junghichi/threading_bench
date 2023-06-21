typedef void** (* Inst)(void**);
#define guard(n) asm("#" #n)

extern Inst prog[];

#define next(n) \
void** next##n(void** ip)\
{\
  guard(n);\
  return ip;\
}

next(1);
next(2);
next(3);
next(4);
next(5);

void** loop(void** ip)
{
  static int count=100000000;

  if (count<=0)
    exit(0);
  count--;
  return prog;
}

Inst prog[] = {next1,next2,next1,next3,next1,next4,next1,next5,next1,loop};

main()
{
  Inst * ip=prog;
  for (;;)
    ip = (*ip)(ip+1);
}

