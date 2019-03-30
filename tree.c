#include "tree.h"

/*Retira dois nós da fila de prioridade, faz o "merge" e manda para a heap*/
Node  *merge_nodes(Heap *heap) {
	if(heap->size != 1){
		Node *left = dequeue(heap);
		Node *right = dequeue(heap);
		lli new_frequency = left->frequency +right->frequency;
		Node *new_node = create_node('*',new_frequency);
		new_node->left = left;
		new_node->right = right;
		enqueue(heap,new_node);
	}else{
		Node *tree = heap->data[1];
        return tree;
	}

}
/*Loop para criar a árvore enquanto o tamanho da fila for diferente de um, pois será o nó raiz*/
Node *create_tree_compact(Heap *heap) {
    int i;
    Node *tree = NULL;
    for(i = heap->size; i >= 1; i--){
        tree = merge_nodes(heap);
    }
    return tree;
}