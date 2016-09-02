LDFLAGS = -lleveldb
CDFLAGS =-std=c99
lx: main.c
	gcc $(LDFLAGS) $(CDFLAGS)  -o lx main.c
run: lx
	./lx
clean:
	rm -f *.o main *.gz *.tar
archive:
	tar -zcvf lx.tar.gz lx
