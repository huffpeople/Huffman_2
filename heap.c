#include "heap.h"

void swap(Node **a, Node **b){

	Node *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

Node *create_node(void* item, lli frequency){
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->item = item;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
	return new_node;
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

void min_heap(Heap *heap, int i){

	int smallest;
	int left_index = 2 * i;
	int right_index = (2 * i) + 1;

	if (left_index <= heap->size && heap->data[left_index]->frequency <= heap->data[i]->frequency) {
		smallest = left_index;
	} else {
		smallest = i;
	}
	if (right_index <= heap->size && heap->data[right_index]->frequency <= heap->data[smallest]->frequency) {
		smallest = right_index;
	}
	if (i != smallest) {
		swap(&heap->data[i], &heap->data[smallest]);
		min_heap(heap,smallest);
	}
}

void enqueue(Heap *heap, Node *new_node){
	
	heap->data[++heap->size] = new_node;
	int index = heap->size;
	int parent_index = heap->size/2;
	while(parent_index >= 1 && heap->data[index]->frequency <= heap->data[parent_index]->frequency){
        swap(&heap->data[index], &heap->data[parent_index]);   
		index = parent_index;
		parent_index = index/2;
	}
}

Node *dequeue (Heap *heap) {

	Node *item = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;
	min_heap(heap,1);
	return item;
}