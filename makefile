CC = gcc


sl: lib main
	$(CC) -o sl main.o -L. -lsl	

lib: sorted-list.o
	ar rcs libsl.a sorted-list.o

main: main.c
	$(CC) -c main.c

sorted-list.o: sorted-list.c sorted-list.h
	$(CC) -c sorted-list.c

clean:
	rm -f *.o sl libsl.a