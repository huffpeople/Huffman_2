#ifndef Heap_H
#define Heap_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	//Item deve ser ponteiro para void
	unsigned char item;
	int frequency;
	struct node *left;
	struct node *right;
}Node;

typedef struct heap {
	int size;
	Node **data;
}Heap;

void print_heap(Heap *heap){
	printf("===> %d\n",heap->size);
	int i;
	for(i = 1;i <= heap->size;i++){
		printf("%c ",heap->data[i]->item);
	}
	printf("\n");
}

void swap(Node **a, Node **b){

	Node *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

Heap *create_heap(){
	Heap *new_heap = (Heap*)malloc(sizeof(Heap));
	new_heap->data = (Node**)malloc(256*sizeof(Node*));
	int i;
	for(i=1;i<256;i++){
		new_heap->data[i] = NULL;
	}
	new_heap->size = 0;
	return new_heap;
}

Node *create_node(int item, int frequency){
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->item = item;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
	return new_node;
}

void min_heap(Heap *heap, int i)
{
	int smallest;
	int left_index = 2 * i;
	int right_index = (2 * i) + 1;

	/*Verifica se o indice está dentro do limite do array,
	e se o valor do nó esquerdo for menor que o nó do pai*/
	if (left_index <= heap->size && heap->data[left_index]->frequency <= heap->data[i]->frequency) {
		/*Se menor que o nó pai, devemos trocar com o nó pai*/
		smallest = left_index;
	}
  else {
		/*Se não for menor, então o seu pai já é o menor*/
		smallest = i;
	}
	/*Verifica se o indice está dentro do limite do array,
	se não estiver, verificar se o nó da direita é menor
	(Ou menor que o pai, ou menor que o nó esquerdo)*/
	if (right_index <= heap->size && heap->data[right_index]->frequency <= heap->data[smallest]->frequency) {
		/*Se menor, significa que ele é o menor de todos*/
		smallest = right_index;
	}
	/*Verificar se o nó raiz já é o menor, se for, não precisa
	haver trocas*/
	if (i != smallest) {
		swap(&heap->data[i], &heap->data[smallest]);
		/*Chama recursivamente até manter a propriedade da heap*/
		min_heap(heap,smallest);
	}
}

/*Receber as frequencias e criar a heap*/
void enqueue(Heap *heap, Node *new_node)
{
	/*Cria um nó com a frequencia e faz a heap apontar para esse nó*/

	heap->data[++heap->size] = new_node;
	/*Recebe o indice do novo nó adicionado*/
	int index = heap->size;
	/*Pai no do nó inserido*/
	int parent_index = heap->size/2;
	/*Enquanto o nó inserido for menor que o seu pai, fazer as trocas*/
	while(parent_index >= 1 && heap->data[index]->frequency <= heap->data[parent_index]->frequency){

        swap(&heap->data[index], &heap->data[parent_index]);
		/*Pai atual será o novo filho*/
		index = parent_index;
		/*Pai do novo filho*/
		parent_index = index/2;
	}
}

Node *dequeue (Heap *heap)
{
	/*Retira o nó da raiz pois é o menor*/
	Node *item = heap->data[1];
	/*Coloca o ultimo nó na raiz*/
	heap->data[1] = heap->data[heap->size];
	/*Diminui o tamanho da heap, pois mandamos o ultimo nó
	para a raiz*/
	heap->size--;
	/*Como alteramos a propriedade da heap, devemos restaura-la*/
	min_heap(heap,1);
	return item;
}

/*Retira dois nós, faz o merge e manda para a heap*/
Node  *merge_nodes(Heap *heap)
{
	if(heap->size != 1){
		Node *left = dequeue(heap);
		//print_heap(heap);
		Node *right = dequeue(heap);
		int item = left->frequency +right->frequency;
		Node *new_node = create_node('*',item);
		new_node->left = left;
		new_node->right = right;
		enqueue(heap,new_node);
	}
  else{
		Node *tree = heap->data[1];
        return tree;
	}
}

#endif
