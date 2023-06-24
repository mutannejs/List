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

int popBackList(sList l, void *e) {
	//se !l ou se a lista estiver vazia
	if (!l || emptyList(l))
		return 1;
	//aloca um node
	sNode *no = l->sentinela->ant;
	//atualiza o encadeamento da lista
	l->sentinela->ant = no->ant;
	l->sentinela->ant->prox = no->prox;
	l->sentinela->prox->ant = no->ant;
	//se e existe aponta ele para o elemento a ser removido
	if (e)
		e = no->elem;
	else//caso contrário, libera o elemento
		free(no->elem);
	//libera o node e atualiza a qtd de nós da lista
	free(no);
	l->qtd--;
	return 0;
}

int popFrontList(sList l, void *e) {
	//se !l ou se a lista estiver vazia
	if (!l || emptyList(l))
		return 1;
	//aloca um node
	sNode *no = l->sentinela->prox;
	//atualiza o encadeamento da lista
	l->sentinela->prox = no->prox;
	l->sentinela->ant->prox = no->prox;
	l->sentinela->prox->ant = no->ant;
	//se e existe aponta ele para o elemento a ser removido
	if (e)
		e = no->elem;
	else//caso contrário, libera o elemento
		free(no->elem);
	//libera o node e atualiza a qtd de nós da lista
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

void* searchlist(sList l, void *key, sIter i) {
	//se !l, !key ou !cmp
	if (!l || !key || !l->cmp)
		return NULL;
	sIter it;
	void *r;
	//percorre toda a lista
	for (it = createIt(l); !endLoop(it); nextIt(it)) {
		//se encontrou o node com a chave passada
		if (!l->cmp(key, returnIt(it))) {
			//se i existe aponta ele para o node com a chave passada
			if (i)
				i->node = it->node;
			//libera o iterador criado no inicio do loop
			r = returnIt(it);
			freeIt(it);
			//retorna o elemento pesquisado
			return r;
		}
	}
	//libera o iterador criado no inicio do loop
	freeIt(it);
	return NULL;
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
	while (!popBackList(l, NULL));
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
	else
		i->node = i->node->prox;
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

int popIt(sIter i, void *e) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no = i->node;
	i->node->ant->prox = i->node->prox;
	i->node->prox->ant = i->node->ant;
	if (sizeList(i->lista) == 1)
		i->node = NULL;
	else
		nextIt(i);

	if (e)
		e = no->elem;
	else
		free(no->elem);
	free(no);
	i->lista->qtd--;

	return 0;
}

int popBeforeIt(sIter i, void *e) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no;
	if (sizeList(i->lista) == 1) {
		popIt(i, NULL);
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
	if (e)
		e = no->elem;
	else
		free(no->elem);
	free(no);
	i->lista->qtd--;

	return 0;
}

int popNextIt(sIter i, void *e) {
	if (!i || emptyList(i->lista))
		return 1;

	sNode *no;
	if (sizeList(i->lista) == 1) {
		popIt(i, NULL);
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
	if (e)
		e = no->elem;
	else
		free(no->elem);
	free(no);
	i->lista->qtd--;

	return 0;
}

void* returnIt(sIter i) {
	if (!i)
		return NULL;
	else
		return i->node->elem;
}

int endLoop(sIter i) {
	//se !i retorna fim de loop
	if (!i)
		return 1;
	//se a lista está vazia ou se o nextIt levou do fim da lista até o início
	else if (emptyList(i->lista) || i->loop) {
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
