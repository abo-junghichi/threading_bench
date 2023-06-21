CC=gcc -Wall -pedantic -Wextra -Wstrict-aliasing=1 -O3 \
-falign-jumps=16 -march=native \
--param min-crossjump-insns=99 --param max-grow-copy-bb-insns=99
#-falign-jumps=32 #-falign-labels=16 #-march=native #-fno-reorder-blocks
DEP=gcc -MM
SRC=subroutine.c direct.c switch.c switch-unre.c indirect.c bytecode.c token.c delay.c direct-delay.c delay-n.c call.c call-eax.c call-two.c nostradamus.c tailcall.c dalvik-mterp.c
DEPENDS=$(patsubst %.c,%.d,$(SRC))
BENCH_MARKS=$(patsubst %.c,%.out,$(SRC))
ASM=$(patsubst %.c,%.s,$(SRC))

DO_BENCH=time
# DO_BENCH=/usr/src/linux/tools/perf/perf stat

%.s: %.c
	$(CC) -S -o $@ $<
%.out: %.s
	$(CC) -o $@ $<
%.d: %.c
	$(DEP) -o $@ $<
default: clean

clean :
	rm -f *.o *.out *.d *.s

all : $(BENCH_MARKS) $(ASM)

bench : all
	for i in $(BENCH_MARKS) ; do echo -n $$i ; $(DO_BENCH) ./$$i ; done

-include $(DEPENDS)
