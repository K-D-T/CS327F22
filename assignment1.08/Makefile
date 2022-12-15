make: main.cpp
	g++ main.cpp functions.cpp -o a1.08 -lm -lncurses
clean:
	rm -f a1.08 seg
debug:
	g++ -g -o seg main.cpp functions.cpp -lncurses
run:
	gdb ./seg
split:	
	vim -O functions.cpp functions.h
edit:
	vim -O ../assignment1.08/functions.cpp ../assignment1.07/functions.cpp

