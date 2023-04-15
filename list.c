/*
 * Lista duplamente encadeada com iterador
 * 
 * */
 
#include "list.h"

sList allocList(long size) {
	//aloca a lista
	sList l = malloc(sizeof(struct sLista));
	if (!l)
		return NULL;
	l->sentinela = malloc(sizeof(sNode));
	if (!l->sentinela)
		return NULL;
	//seta valores da lista
	l->qtd = 0;
	l->size = size;
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
	no->elem = malloc(l->size);
	if (!no->elem)
		return 1;
	//seta os valores do node
	memcpy(no->elem, e, l->size);
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
	no->elem = malloc(l->size);
	if (!no->elem)
		return 1;
	//seta os valores do node
	memcpy(no->elem, e, l->size);
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

void* backList(sList l) {
	if (!l || emptyList(l))
		return NULL;
	return l->sentinela->ant->elem;
}

void* frontList(sList l) {
	if (!l || emptyList(l))
		return NULL;
	return l->sentinela->prox->elem;
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

sIterator createIt(sList l) {
	if (!l)
		return NULL;
	//aloca o iterador
	sIterator i = malloc(sizeof(struct sIterador));
	if (!i)
		return NULL;
	//seta os valores do iterador
	//aponta o iterador para o primeiro node da lista (se ele existir)
	if (emptyList(l))
		i->node = NULL;
	else
		i->node = l->sentinela->prox;
	i->lista = l;
	//inicia o loop
	i->inicio = NULL;
	startLoop(i);
	return i;
}

void frontIt(sIterator i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else
		i->node = i->lista->sentinela->prox;
	//inicia o loop
	startLoop(i);
}

void backIt(sIterator i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else
		i->node = i->lista->sentinela->ant;
	//inicia o loop
	startLoop(i);
}

void beforeIt(sIterator i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else if (i->node->ant == i->lista->sentinela)//pula o sentila
		i->node = i->node->ant->ant;
	else
		i->node = i->node->ant;
	i->vistos -= 1;
}

void nextIt(sIterator i) {
	if (!i)
		return;
	if (emptyList(i->lista))
		i->node = NULL;
	else if (i->node->prox == i->lista->sentinela)//pula o sentila
		i->node = i->node->prox->prox;
	else
		i->node = i->node->prox;
	i->vistos += 1;
}

int pushBeforeIt(sIterator i, void *e) {
	if (!i)
		return 1;
	
	if (!emptyList(i->lista)) {
		sNode *no = (sNode*) malloc(sizeof(sNode));
		if (!no)
			return 1;
		no->elem = malloc(i->lista->size);
		if (!no->elem)
			return 1;
		memcpy(no->elem, e, i->lista->size);
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
	
	if (i->vistos > 0)
		i->vistos += 1;

	return 0;
}

int pushNextIt(sIterator i, void *e) {
	if (!i)
		return 1;

	if (!emptyList(i->lista)) {
		sNode *no = (sNode*) malloc(sizeof(sNode));
		if (!no)
			return 1;
		no->elem = malloc(i->lista->size);
		if (!no->elem)
			return 1;
		memcpy(no->elem, e, i->lista->size);
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
	
	if (i->vistos < 0)
		i->vistos -= 1;

	return 0;
}

int popIt(sIterator i) {
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
	if (i->lista->qtd == 0)
		i->node = NULL;

	if (i->vistos < 0)
		i->vistos += 1;

	return 0;
}

int popBeforeIt(sIterator i) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no;
	if (sizeList(i->lista) == 1) {
		popIt(i);
	}
	else if (i->node->ant == i->lista->sentinela) {
		no = i->node->ant->ant;
		i->node->ant->ant->ant->prox = i->node->ant;
		i->node->ant->ant = i->node->ant->ant->ant;
	}
	else {
		no = i->node->ant;
		i->node->ant->ant->prox = i->node;
		i->node->ant = i->node->ant->ant;
	}
	free(no->elem);
	free(no);
	i->lista->qtd--;
	if (i->lista->qtd == 0)
		i->node = NULL;

	if (i->vistos > 0)
		i->vistos -= 1;

	return 0;
}

int popNextIt(sIterator i) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no;
	if (sizeList(i->lista) == 1) {
		popIt(i);
	}
	else if (i->node->prox == i->lista->sentinela) {
		no = i->node->prox->prox;
		i->node->prox->prox->prox->ant = i->node->prox;
		i->node->prox->prox = i->node->prox->prox->prox;
	}
	else {
		no = i->node->prox;
		i->node->prox->prox->ant = i->node;
		i->node->prox = i->node->prox->prox;
	}
	free(no->elem);
	free(no);
	i->lista->qtd--;
	if (i->lista->qtd == 0)
		i->node = NULL;

	if (i->vistos < 0)
		i->vistos += 1;

	return 0;
}

void* returnIt(sIterator i) {
	if (!i)
		return NULL;
	else
		return i->node->elem;
}

void startLoop(sIterator i) {
	if (!i || emptyList(i->lista))
		return;
	i->inicio = i->node;
	i->vistos = 0;
}

int endLoop(sIterator i) {
	//se !i retorna fim de loop
	if (!i)
		return 1;
	//se a lista está vazia ou foi percorrido toda a lista desde startLoop,
	//seta i->inicio como NULL e retorna fim de loop
	else if (emptyList(i->lista) || (i->node == i->inicio && i->vistos != 0)) {
		i->inicio = NULL;
		return 1;
	}
	else {
		return 0;
	}
}

void freeIt(sIterator i) {
	if (i)
		free(i);
}
