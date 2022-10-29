CC=cc
CFLAGS=-Wall

test: test.c vector.o
	$(CC) $(CFLAGS) $^ -o $@

vector.o: vector.c vector.h
	$(CC) $< -c

clean:
	rm -f *.o test
