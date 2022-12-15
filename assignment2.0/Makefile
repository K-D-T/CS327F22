make: main.cpp
	g++ main.cpp build.cpp -o a2.0 -lm -lncurses
clean:
	rm -f a2.0 seg
debug:
	g++ -g -o seg main.cpp build.cpp -lncurses
run:
	gdb ./seg
split:	
	vim -O build.cpp build.h
edit:
	g++ main.cpp build.h -o a2.0 -lm -lncurses

