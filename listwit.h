/*
 * Lista duplamente encadeada com sentinela e iterador
 * 
 * */

#ifndef LISTWIT_H
#define LISTWIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNo {
	void *elem;
	struct sNo *ant, *prox;
} sNode;

typedef struct sLista {
	long qtd;
	size_t tam;
	struct sNo *sentinela;
	int (*cmp)(const void *key, const void *elem);
} *sList;

typedef struct sIterador {
	struct sNo *node;
	struct sLista *lista;
	int loop;
} *sIter;

/**
 * Cria uma lista
 * Uma lista é originalmente vazia
 * 
 * type	: deve ser o tipo dos dados que serão inseridos na lista
 * cmp	: função de comparação entre dados do mesmo tipo passado como argumento.
 * 			  A função deve ter a assinatura seguindo o padrão
 * 			  int (*cmp)(const void *, const void *), deve retornar -1 se o primeiro
 * 			  argumento é menor que o segundo, 0 se é igual e 1 se é maior
 * 			  Exemplo de assinatura: int cmpString(const void *str1, const void *str2)
 * retorno	: uma variável do tipo sList
 * 
 * Exemplo da criação de uma lista que guarda itens do tipo double, com a
 * 	função de comparação chamada cmpDouble:
 * sList l = createList(double, cmpDouble);
 * */
#define createList(type, cmp) __alocaLista(sizeof(type), cmp)

/**
 * Função privada para alocar uma lista. Baixo nível para createList()
 * */
sList __alocaLista(long tam, int (*cmp)(const void *, const void *));

/**
 * Insere um elemento no fim da lista
 * 
 * l  : a lista usada
 * *e : ponteiro para o elemento que será inserido
 * retorno : retorna 1 se o elemento foi inserido com sucesso, e 0 se não
 * 			 possível inserir
 * 
 * Ex:	pushBackList(l, &e);
 * */
int pushBackList(sList l, void *e);

/* Insere um elemento no início da lista
 * Deve ser passado como primeiro argumento o endereço da lista usada, e segundo argumento o endereço do elemento que será guardado
 * Não tem retorno
 * Ex:	pushFrontList(&l, &e);
 * */
int pushFrontList(sList l, void *e);

/* Remove o elemento no fim da lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna 1 caso tenha sido removido o elemento, e 0 caso a lista esteja vazia
 * Ex:	popBackList(&l);
 * */
int popBackList(sList l);

/* Remove o elemento no início da lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna 1 caso tenha sido removido o elemento, e 0 caso a lista esteja vazia
 * Ex:	popFrontList(&l);
 * */
int popFrontList(sList l);

/* Retorna um ponteiro para o fim da lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna um ponteiro para o conteúdo no fim da lista (deve ser usado type casting), caso a lista esteja vazia retorna NULL
 * Ex:	double *d = (double*) backList(&l);
 * */
void* backList(sList l);

/* Retorna um ponteiro para o início da lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna um ponteiro para o conteúdo no início da lista (deve ser usado type casting), caso a lista esteja vazia retorna NULL
 * Ex:	double *d = (double*) frontList(&l);
 * */
void* frontList(sList l);

/* Retorna elemento com a chave informada
 * */
void* searchList(sList l, void *key, sIter i);

/* Informa se a lista está vazia
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna 1 caso a lista esteja vazia, e 0 caso tenha ao menos um elemento
 * Ex:	if (emptyList(&l)) {}
 * */
int emptyList(sList l);

/* Informa o tamanho da lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna quantos elementos a lista possui
 * Ex:	long tamLista = sizeList(&l);
 * */
long sizeList(sList l);

/* Libera a lista
 * Deve ser passado como argumento o endereço da lista que deve ser liberada
 * Não tem retorno
 * Ex:	freeList(&l);
 * */
void freeList(sList l);


/* 
 * Protótipo das funções do Iterador
 * 
 * */

/* Cria um iterador para uma lista
 * Deve ser passado como argumento o endereço da lista usada
 * Retorna um iterador para a lista, se referindo para o início dela
 * Ex:	sIterador i = criaIt(&l);
 * */
sIter createIt(sList l);

/* Itera para o primeiro elemento na lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Não tem retorno
 * Ex:	iteraInicio(&i);
 * */
void frontIt(sIter i);

/* Itera para o último elemento na lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Não tem retorno
 * Ex:	iteraFim(&i);
 * */
void backIt(sIter i);

/* Itera para o elemento anterior na lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Não tem retorno
 * Ex:	iteraAnterior(&i);
 * */
void beforeIt(sIter i);

/* Itera para o próximo elemento na lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Não tem retorno
 * Ex:	iteraProximo(&i);
 * */
void nextIt(sIter i);

/* Insere um elemento na lista antes da posição atual do iterador
 * Deve ser passado como primeiro argumento o endereço do iterador usado, e segundo argumento o endereço do elemento que será guardado
 * Não tem retorno
 * Ex:	insereAntIt(&i, &e);
 * */
int pushBeforeIt(sIter i, void *e);

/* Insere um elemento na lista depois da posição atual do iterador
 * Deve ser passado como primeiro argumento o endereço do iterador usado, e segundo argumento o endereço do elemento que será guardado
 * Não tem retorno
 * Ex:	insereProxIt(&i, &e);
 * */
int pushNextIt(sIter i, void *e);

/* Remove o elemento da lista que está sendo referenciado pelo iterador
 * Deve ser passado como argumento o endereço do iterador usado (o iterador passa a apontar para o elemento seguinte)
 * Retorna 1 caso tenha sido removido o elemento, e 0 caso a lista esteja vazia
 * Ex:	removeIt(&i, &e);
 * */
int popIt(sIter i);

/* Remove o elemento que está na lista antes da posição atual do iterador
 * Deve ser passado como argumento o endereço do iterador usado
 * Retorna 1 caso tenha sido removido o elemento, e 0 caso a lista esteja vazia
 * Ex:	removeAntIt(&i, &e);
 * */
int popBeforeIt(sIter i);

/* Remove o elemento que está na lista depois da posição atual do iterador
 * Deve ser passado como argumento o endereço do iterador usado
 * Retorna 1 caso tenha sido removido o elemento, e 0 caso a lista esteja vazia
 * Ex:	removeProxIt(&i, &e);
 * */
int popNextIt(sIter i);

/* Retorna um ponteiro para o elemento referenciado pelo iterador
 * Deve ser passado como argumento o endereço do iterador usado
 * Retorna um ponteiro para o conteúdo na lista referenciado pelo iterador (deve ser usado type casting), caso a lista esteja vazia retorna NULL
 * Ex:	double *d = (double*) retornaItera(&i);
 * */
void* returnIt(sIter i);

/* Informa se o iterador está referenciando para o início da lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Retorna 1 caso o iterador esteja referenciando para o início da lista, e 0 caso não esteja
 * Ex:	if (inicioIt(&i)) {}
 * */
int beginIt(sIter *i);

/* Informa se o iterador está referenciando para o fim da lista
 * Deve ser passado como argumento o endereço do iterador usado
 * Retorna 1 caso o iterador esteja referenciando para o fim da lista, e 0 caso não esteja
 * Ex:	if (fimIt(&i)) {}
 * */
int endIt(sIter *i);

/* Cria uma cópia do iterador
 * */
sIter copyIt(sIter i);

/* Verifica se foi feito um loop completo (de Front até Back)
 * */
int endLoop(sIter i);

/* Libera espço alocado pelo iterador
 * */
void freeIt(sIter i);

#if 0

	int pushBackIt(sIterator i, void *e);

	int pushFrontIt(sIterator i, void *e);

	void startLoop(sIterator i);

	/* Informa se o iterador está referenciando para o início da lista
	 * Deve ser passado como argumento o endereço do iterador usado
	 * Retorna 1 caso o iterador esteja referenciando para o início da lista, e 0 caso não esteja
	 * Ex:	if (inicioIt(&i)) {}
	 * */
	int inicioIt(sIterator *i);

	/* Informa se o iterador está referenciando para o fim da lista
	 * Deve ser passado como argumento o endereço do iterador usado
	 * Retorna 1 caso o iterador esteja referenciando para o fim da lista, e 0 caso não esteja
	 * Ex:	if (fimIt(&i)) {}
	 * */
	int fimIt(sIterator *i);

	// Exemplo de loop usando iterador, do início ao fim da lista
	/* 
	 * sIterador it = criaIt(&l);
	 * do {
	 * 	//processo
	 * 	iteraProximo(&it);
	 * } while (inicioIt(&it));
	 * 
	 * */
#endif

#endif
