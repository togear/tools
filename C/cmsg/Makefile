LDADD = -L./ 
FLAG = -Wall -O2 -D_USE_STRUCT
#FLAG = -Wall -O2

all: fd-passing-test fd-passing-offset fd-passing-multi

fd-passing-test: fd-passing.o stderr.o
	gcc -o fd-passing fd-passing.o stderr.o  $(LDADD) $(FLAG)

fd-passing-offset: fd-passing-offset.o stderr.o
	gcc -o fd-passing-offset fd-passing-offset.o stderr.o  $(LDADD) $(FLAG)

fd-passing-multi: fd-passing-multi.o stderr.o
	gcc -o fd-passing-multi fd-passing-multi.o stderr.o  $(LDADD) $(FLAG)

fd-passing.o: fd-passing.c
	gcc -c fd-passing.c $(FLAG)

fd-passing-offset.o: fd-passing-offset.c
	gcc -c fd-passing-offset.c $(FLAG)

stderr.o: stderr.c
	gcc -c stderr.c $(FLAG)

clean:
	@rm -f *.o fd-passing fd-passing-offset fd-passing-multi
