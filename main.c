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

	double chave = 10.5;
	sList l = createList(double, cmpDouble);

	for (double i = 5.5; i < 20.5; i += 1)
		pushBackList(l, &i);

	sIterator it = createIt(l);
	searchlist(l, &chave, it);

	for (startLoop(it); !endLoop(it); beforeIt(it)) {
		if (it->vistosLoop == 0) {
			printf("\t%ld\n", it->vistosLoop);
			chave = 0.1;
			pushBeforeIt(it, &chave);
			chave = 0.2;
			pushNextIt(it, &chave);
		}
		else if (it->vistosLoop == -3) {
			printf("\t%ld\n", it->vistosLoop);
			chave = 0.3;
			pushBeforeIt(it, &chave);
			chave = 0.4;
			pushNextIt(it, &chave);
			nextIt(it);
			nextIt(it);
			chave = 0.5;
			pushBeforeIt(it, &chave);
			chave = 0.6;
			pushNextIt(it, &chave);
		}
		else if (it->vistosLoop == -7) {
			printf("\t%ld\n", it->vistosLoop);
			chave = 0.7;
			pushFrontIt(it, &chave);
			printf("\t%ld\n", it->vistosLoop);
			chave = 0.8;
			pushBackIt(it, &chave);
			printf("\t%ld\n", it->vistosLoop);
		}
		else if (it->vistosLoop == -10) {
			printf("\t-10\n");
			chave = 0.9;
			pushFrontIt(it, &chave);
			chave = 0.11;
			pushBackIt(it, &chave);
		}
		else if (it->vistosLoop == -12) {
			printf("\t-12\n");
			chave = 0.12;
			pushFrontIt(it, &chave);
			chave = 0.13;
			pushBackIt(it, &chave);
		}
		printf("no: %.2lf\n", *((double*)returnIt(it)));
	}

	return 0;

}
