LDFLAGS = -lleveldb
CDFLAGS =-std=c99
all: main.c
	gcc $(LDFLAGS) $(CDFLAGS)  -o test_demo main.c leveldb.c
run: test_demo
	./test_demo
clean:
	rm -f *.o main *.gz *.tar test_demo
archive:
	tar -zcvf test_demo.tar.gz test_demo
