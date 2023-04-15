all: compile
	@ gcc -o run main.c list.o -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0

compile:
	@ gcc -c list.c -std=c99 -Wall -Wextra -Wno-unused-result -Wpedantic -O0
