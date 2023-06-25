/*
 * Lista duplamente encadeada com sentinela e iterador
 * 
 * */
 
#include "listwit.h"

sList __alocaLista(long size, int (*cmp)(const void *, const void *)) {
	//aloca a lista
	sList l = malloc(sizeof(struct sLista));
	if (!l)
		return NULL;
	l->sentinela = malloc(sizeof(sNode));
	if (!l->sentinela)
		return NULL;
	//seta valores da lista
	l->qtd = 0;
	l->tam = size;
	l->cmp = cmp;
	//encadeia o sentinela
	l->sentinela->ant = l->sentinela->prox = l->sentinela;
	//retorna o endereço da lista
	return l;
}

int pushBackList(sList l, void *e) {
	if (!l || !e)
		return 1;
	//aloca um node
	sNode *no = (sNode*) malloc(sizeof(sNode));
	if (!no)
		return 1;
	no->elem = malloc(l->tam);
	if (!no->elem)
		return 1;
	//seta os valores do node
	memcpy(no->elem, e, l->tam);
	no->ant = l->sentinela->ant;
	no->prox = l->sentinela;
	//atualiza a lista
	l->sentinela->ant->prox = no;
	l->sentinela->ant = no;
	l->qtd++;
	return 0;
}

int pushFrontList(sList l, void *e) {
	if (!l || !e)
		return 1;
	//aloca um node
	sNode *no = (sNode*) malloc(sizeof(sNode));
	if (!no)
		return 1;
	no->elem = malloc(l->tam);
	if (!no->elem)
		return 1;
	//seta os valores do node
	memcpy(no->elem, e, l->tam);
	no->ant = l->sentinela;
	no->prox = l->sentinela->prox;
	//atualiza a lista
	l->sentinela->prox->ant = no;
	l->sentinela->prox = no;
	l->qtd++;
	return 0;
}

int popBackList(sList l) {
	//se !l ou se a lista estiver vazia
	if (!l || emptyList(l))
		return 1;
	//aloca um node
	sNode *no = l->sentinela->ant;
	//atualiza o encadeamento da lista
	l->sentinela->ant = no->ant;
	l->sentinela->ant->prox = no->prox;
	l->sentinela->prox->ant = no->ant;
	//libera o node e atualiza a qtd de nós da lista
	free(no->elem);
	free(no);
	l->qtd--;
	return 0;
}

int popFrontList(sList l) {
	//se !l ou se a lista estiver vazia
	if (!l || emptyList(l))
		return 1;
	//aloca um node
	sNode *no = l->sentinela->prox;
	//atualiza o encadeamento da lista
	l->sentinela->prox = no->prox;
	l->sentinela->ant->prox = no->prox;
	l->sentinela->prox->ant = no->ant;
	//libera o node e atualiza a qtd de nós da lista
	free(no->elem);
	free(no);
	l->qtd--;
	return 0;
}

int backList(sList l, void *p) {
	if (!l || !p || emptyList(l))
		return 1;
	memcpy(p, l->sentinela->ant->elem, l->tam);
	return 0;
}

int frontList(sList l, void *p) {
	if (!l || !p || emptyList(l))
		return 1;
	memcpy(p, l->sentinela->prox->elem, l->tam);
	return 0;
}

/* Atualiza o valor do elemento no fim da lista
 * */
int setBackList(sList l, void *e) {
	if (!l || emptyList(l))
		return 1;
	memcpy(l->sentinela->ant->elem, e, l->tam);
	return 0;
}

/* Atualiza o valor do elemento no início da lista
 * */
int setFrontList(sList l, void *e) {
	if (!l || emptyList(l))
		return 1;
	memcpy(l->sentinela->prox->elem, e, l->tam);
	return 0;
}

int searchList(sList l, void *key, sIter i) {
	//se !l, !key ou !cmp
	if (!l || !key || !l->cmp)
		return 0;
	sIter it;
	void *retIt = malloc(l->tam);
	//percorre toda a lista
	for (it = createIt(l); !endLoop(it); nextIt(it)) {
		//se encontrou o node com a chave passada
		returnIt(it, retIt);
		if (!l->cmp(key, retIt)) {
			//se i existe aponta ele para o node com a chave passada
			if (i)
				i->node = it->node;
			//libera o iterador criado no inicio do loop
			freeIt(it);
			return 1;
		}
	}
	//libera o iterador criado no inicio do loop
	freeIt(it);
	return 0;
}

int emptyList(sList l) {
	if (!l)
		return -1;
	if (l->qtd == 0)
		return 1;
	else
		return 0;
}

long sizeList(sList l) {
	if (!l)
		return -1;
	return l->qtd;
}

void freeList(sList l) {
	if (!l)
		return;
	//se a lista não estiver vazia, popBackList retornará 0
	while (!popBackList(l));
	//libera o sentinela e a própria lista
	free(l->sentinela);
	free(l);
}


/* 
 * Implemetação das funçõees do Iterador
 * 
 * */

sIter createIt(sList l) {
	if (!l)
		return NULL;
	//aloca o iterador
	sIter i = malloc(sizeof(struct sIterador));
	if (!i)
		return NULL;
	//aponta o iterador para o primeiro node da lista (se ele existir)
	if (emptyList(l))
		i->node = NULL;
	else
		i->node = l->sentinela->prox;
	i->lista = l;
	i->loop = 0;
	return i;
}

void frontIt(sIter i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else
		i->node = i->lista->sentinela->prox;
	i->loop = 0;
}

void backIt(sIter i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else
		i->node = i->lista->sentinela->ant;
}

void beforeIt(sIter i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else if (i->node->ant == i->lista->sentinela)//pula o sentila
		i->node = i->node->ant->ant;
	else
		i->node = i->node->ant;
}

void nextIt(sIter i) {
	if (!i)
		return;
	i->loop = 0;
	if (emptyList(i->lista))
		i->node = NULL;
	else if (i->node->prox == i->lista->sentinela) {//pula o sentila
		i->node = i->node->prox->prox;
		i->loop = 1;
	}
	else {
		i->node = i->node->prox;
	}

}

int pushBeforeIt(sIter i, void *e) {
	if (!i)
		return 1;
	
	if (!emptyList(i->lista)) {
		sNode *no = (sNode*) malloc(sizeof(sNode));
		if (!no)
			return 1;
		no->elem = malloc(i->lista->tam);
		if (!no->elem)
			return 1;
		memcpy(no->elem, e, i->lista->tam);
		no->ant = i->node->ant;
		no->prox = i->node;
		i->node->ant->prox = no;
		i->node->ant = no;
		i->lista->qtd++;
	}
	else {
		pushFrontList(i->lista, e);
		frontIt(i);
	}

	return 0;
}

int pushNextIt(sIter i, void *e) {
	if (!i)
		return 1;

	if (!emptyList(i->lista)) {
		sNode *no = (sNode*) malloc(sizeof(sNode));
		if (!no)
			return 1;
		no->elem = malloc(i->lista->tam);
		if (!no->elem)
			return 1;
		memcpy(no->elem, e, i->lista->tam);
		no->ant = i->node;
		no->prox = i->node->prox;
		i->node->prox->ant = no;
		i->node->prox = no;
		i->lista->qtd++;
	}
	else {
		pushFrontList(i->lista, e);
		frontIt(i);
	}

	return 0;
}

int popIt(sIter i) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no = i->node;
	i->node->ant->prox = i->node->prox;
	i->node->prox->ant = i->node->ant;
	if (sizeList(i->lista) == 1)
		i->node = NULL;
	else
		nextIt(i);

	free(no->elem);
	free(no);
	i->lista->qtd--;

	return 0;
}

int popBeforeIt(sIter i) {
	if (!i || emptyList(i->lista))
		return 1;

	sIter it = copyIt(i);
	beforeIt(it);
	popIt(it);

	return 0;
}

int popNextIt(sIter i) {
	if (!i || emptyList(i->lista))
		return 1;

	sIter it = copyIt(i);
	nextIt(it);
	popIt(it);

	return 0;
}

int beginIt(sIter i) {
	if (i->node == i->lista->sentinela->prox && !emptyList(i->lista))
		return 1;
	else
		return 0;
}

int endIt(sIter i) {
	if (i->node == i->lista->sentinela->ant && !emptyList(i->lista))
		return 1;
	else
		return 0;
}

int returnIt(sIter i, void *p) {
	if (!i || !i->node || !p)
		return 1;
	memcpy(p, i->node->elem, i->lista->tam);
	return 0;
}

int setIt(sIter i, void *e) {
	if (!i || !i->node || !e)
		return 1;
	memcpy(i->node->elem, e, i->lista->tam);
	return 0;
}

sIter copyIt(sIter i) {
	sIter j = createIt(i->lista);
	j->node = i->node;
	return j;
}

int endLoop(sIter i) {
	//se !i retorna fim de loop
	if (!i)
		return 1;
	//se a lista está vazia ou se o nextIt levou do fim da lista até o início
	if (emptyList(i->lista) || i->loop) {
		i->loop = 0;
		return 1;
	}
	else {
		return 0;
	}
}

void freeIt(sIter i) {
	if (i)
		free(i);
}
