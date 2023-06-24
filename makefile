run: main.c list.o
	gcc -o run main.c list.o -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0

list.o: list.c list.h
	gcc -c list.c -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0

clean:
	rm run list.o
