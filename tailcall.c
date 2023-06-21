#define guard(n) asm("#" #n)

extern void * prog[];

#define NEXT (((void (*)(void*))*ip)(ip+1))

void next1(void ** ip)
{
  guard(1);
  NEXT;
}

void next2(void ** ip)
{
  guard(2);
  NEXT;
}

void next3(void ** ip)
{
  guard(3);
  NEXT;
}

void next4(void ** ip)
{
  guard(4);
  NEXT;
}

void next5(void ** ip)
{
  guard(5);
  NEXT;
}

void loop(void ** ip)
{
  static int count=100000000;

  if (count<=0)
    exit(0);
  count--;
  ip=prog;
  NEXT;
}

void * prog[] = {next1,next2,next1,next3,next1,next4,next1,next5,next1,loop};

main()
{
  void ** ip=prog;
  for (;;)
    NEXT;
}

