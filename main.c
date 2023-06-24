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
	printf("front:%.2lf  back:%.2lf\n\n", *((double*)frontList(l)), *((double*)backList(l)));

	for (sIter it = createIt(l); !endLoop(it); nextIt(it)) {
		chave = *((double*)returnIt(it));
		if (chave < 10) {
			if (popIt(it, NULL))
				printf("erro ");
			if (popBeforeIt(it, NULL))
				printf("erro ");
			printf("removido: %.2lf\n", chave);
		}
		else
			printf("no: %.2lf\n", chave);
	}

	return 0;

}
