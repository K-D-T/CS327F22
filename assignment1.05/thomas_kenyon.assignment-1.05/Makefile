make: main.c
	gcc main.c functions.c -o a1.05 -lm -lncurses
clean:
	rm -f a1.05
debug:
	gcc -g -o seg main.c functions.c -lncurses
run:
	gdb ./seg
split:	
	vim -O functions.c functions.h

