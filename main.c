/*
 * Testes da lista
 * 
 * */

#include <stdio.h>
#include "listwit.h"

int cmpDouble(const void *num1, const void *num2) {
	if ( (*((const double *)num1)) > (*((const double *)num2)) )
		return 1;
	if ( (*((const double *)num1)) < (*((const double *)num2)) )
		return -1;
	return 0;
}

int main() {

	double chave = 35.8;
	sList l = createList(double, cmpDouble);

	for (double i = 5.5; i < 20.5; i += 1)
		pushBackList(l, &i);

	frontList(l, &chave);
	printf("front:%.2lf", chave);
	backList(l, &chave);
	printf("  back:%.2lf\n\n", chave);

	sIter it = createIt(l);
	while (!endLoop(it)) {
		returnIt(it, &chave);
		if (chave < 8) {
			printf("removidos: %.2lf", chave);

			sIter it2 = copyIt(it);
			nextIt(it2);
			returnIt(it2, &chave);
			freeIt(it2);

			popNextIt(it);
			popIt(it);
			printf("  %.2lf\n", chave);
		}
		else if (chave < 12) {
			popIt(it);
			printf("removidos: %.2lf", chave);

			sIter it2 = copyIt(it);
			beforeIt(it2);
			returnIt(it2, &chave);
			freeIt(it2);

			popBeforeIt(it);
			printf("  %.2lf\n", chave);
		}
		else {
			printf("no: %.2lf\n", chave);
			nextIt(it);
		}
	}

	chave = 12.4;
	if (searchList(l, &chave, it))
		printf("Não encontrou\n");
	chave = 14.5;
	if (searchList(l, &chave, it)) {
		chave = 5.0;
		setIt(it, &chave);
		printf("\n");
	}
	chave = 10.01;
	setFrontList(l, &chave);
	chave = 14.99;
	setBackList(l, &chave);

	for (frontIt(it); !endLoop(it); nextIt(it)) {
		returnIt(it, &chave);
		printf("no: %.2lf\n", chave);
	}

	return 0;

}
