LDADD = -L./ 
FLAG = -Wall -O2

all: rfc1738_test

rfc1738_test: rfc1738_test.o rfc1738.o
	gcc -o rfc1738_test rfc1738_test.o rfc1738.o  $(LDADD) $(FLAG)

rfc1738_test.o: rfc1738_test.c
	gcc -c rfc1738_test.c $(FLAG)

rfc1738.o: rfc1738.c
	gcc -c rfc1738.c $(FLAG)

clean:
	@rm -f *.o rfc1738_test
