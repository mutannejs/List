/*
 * Testes da lista
 * 
 * */

#include <stdio.h>
#include "list.h"

int cmpDouble(const void *num1, const void *num2) {
	if ( (*((const double *)num1)) > (*((const double *)num2)) )
		return 1;
	if ( (*((const double *)num1)) < (*((const double *)num2)) )
		return -1;
	return 0;
}

int main() {

	sList l = createList(double, cmpDouble);

	for (double i = 5.5; i < 20.5; i += 1) {
		pushBackList(l, &i);
	}

	double chave = 10.5;
	double *node = searchlist(l, &chave, NULL);
	printf("dez.cinquenta: %.2lf\n", *node);

	return 0;

}
