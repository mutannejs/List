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

	double chave = 35.8, bef;
	sList l = createList(double, cmpDouble);

	for (double i = 5.5; i < 20.5; i += 1)
		pushBackList(l, &i);
	printf("front:%.2lf  back:%.2lf\n\n", *((double*)frontList(l)), *((double*)backList(l)));

	sIter it = createIt(l);
	while (!endLoop(it)) {
		chave = *((double*)returnIt(it));
		if (chave < 10) {
			if (popIt(it))
				printf("erro ");

			sIter it2 = copyIt(it);
			beforeIt(it2);
			bef = *((double*)returnIt(it2));
			freeIt(it2);

			if (popBeforeIt(it))
				printf("erro ");
			printf("removidos: %.2lf  %.2lf\n", chave, bef);
		}
		else {
			printf("no: %.2lf\n", chave);
			nextIt(it);
		}
	}

	return 0;

}
