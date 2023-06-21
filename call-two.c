typedef struct wip wip;
typedef wip (* Inst)(void**);

struct wip { Inst label; void ** ip; };


wip mkwip (void ** ip){
 wip rtn;
 rtn.ip=ip;
 rtn.label=*ip;
 return rtn;
}

#define guard(n) asm("#" #n)

extern Inst prog[];

#define next(n) \
wip next##n(void **ip)\
{\
  guard(n);\
  return mkwip(ip+1);\
}

next(1);
next(2);
next(3);
next(4);
next(5);

wip loop(void **ip)
{
  static int count=100000000;
  wip rtn;
  if (count<=0)
    exit(0);
  count--;
  return mkwip(prog);
}

Inst prog[] = {next1,next2,next1,next3,next1,next4,next1,next5,next1,loop};

main()
{
  wip iip = mkwip(prog);
  for (;;)
    iip = (*iip.label)(iip.ip);
}

