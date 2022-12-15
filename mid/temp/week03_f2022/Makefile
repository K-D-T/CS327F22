queue_test: main.o queue.o
	gcc main.o queue.o -o queue_test

main.o: main.c queue.h
	gcc -Wall -Werror -g main.c -c

queue.o: queue.c queue.h
	gcc -Wall -Werror -g queue.c -c

clean:
	rm -f *.o queue_test
