run: main.c listwit.o
	gcc -o run main.c listwit.o -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0

listwit.o: listwit.c listwit.h
	gcc -c listwit.c -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0

clean:
	rm run listwit.o
