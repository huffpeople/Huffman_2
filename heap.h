#ifndef heap_h
#define heap_h

#include "header.h"

typedef unsigned char uc;
typedef long long int lli;

typedef struct node{
	void* item;
	lli frequency;
	struct node *left;
	struct node *right;
}Node;

typedef struct heap{
	int size;
	Node **data;
}Heap;

void swap(Node **a, Node **b);

/*Função para criar nós, recebendo a frequencia atual e o caracter*/
Node *create_node(void* item, lli frequency);


/*Declaramos a heap dinamicamente, e fazemos todos as posições
"apontar" para nulo para depois "apontar para um nó"*/
Heap *create_heap();


/*Função que verifica três nós, o nó pai, filho da esquerda e flho da direita,
e sempre verificando se esta dentro dos limites do array, o menor nó é trocado pela raiz,
até que ele seja a própria raiz, assim mantemos a propriedade de heap minima*/
void min_heap(Heap *heap, int i);


/*Receber as frequencias para criar a heap, criamos um novo nó e colocamos no fim da heap.
Como precisamos de uma heap mínima, enquanto o novo nó adicionado for menor que seu "pai",
fazemos a troca com o pai*/
void enqueue(Heap *heap, Node *new_node);

/*Função que retira um nó raiz da heap, colocamos o ultimo nó na raiz,
e diminui o tamanho da heap, dessa forma o excluindo, então restauramos 
a propriedade da heap*/
Node *dequeue (Heap *heap);

#endif

