#include "descompact.h"

Node *create_tree_descompact (Node *tree, FILE *input) {
    uc item;
    fscanf(input,"%c", &item);
    if (item != '*') {
        if (item == '\\') {
            fscanf(input,"%c", &item);
        }
        return create_node(item,0);
    } else {
        tree = create_node(item,0);
        tree->left = create_tree_descompact(tree->left,input);
        tree->right = create_tree_descompact(tree->right,input);
    }
    return tree;
}

lli number_of_bytes (FILE *input) {

	lli count = 0;
	uc byte;
	while (fscanf(input,"%c", &byte) != EOF) {
		count += 1;
	}
	return count;
}

int is_bit_i_set (uc byte, int i) {
	uc mask = 1 << i;
	return mask & byte;
}

Node* put_in_file (FILE *output, Node *tree_aux, Node *tree, int i, uc byte) {
	
	if (is_bit_i_set(byte,i)) {
		tree_aux = tree_aux->right;
	} else {
		tree_aux = tree_aux->left;
	}
	if (tree_aux->left ==  NULL && tree_aux->right == NULL) {
		fprintf(output,"%c", tree_aux->item);
		tree_aux = tree;
	} 
	return tree_aux;
}

void put_caracter_in_file (FILE *input, FILE *output, Node *tree, lli number_bytes, unsigned short int trash) {
	
	Node *tree_aux = tree;
	uc byte;
	int i;
	for (int j = 0; j < number_bytes; j++) {
		fscanf(input,"%c", &byte);
		if ((j == number_bytes - 1) && trash != 0) {
			for (i = 7; i >= trash; i--) {
				tree_aux = put_in_file(output,tree_aux,tree,i,byte);
			}
			break;
		} 
		
		for (i = 7; i >= 0; i--) {
			tree_aux = put_in_file(output,tree_aux,tree,i,byte);
		}	
	}
	fclose(output);
	fclose(input);
}

void descompact() {
	FILE *input;
	FILE *output;
	char name_file[100];
	printf("File name to descompress: \n");
	printf("===> ");
	scanf("%s", name_file);
	input = fopen(name_file,"rb");
	if (input == NULL ) {
		printf("Invalid file\n");
		return;
	}
	char name_file_output[100];
	int i;
	for (i = 0; i < strlen(name_file) - 5; i++) {
		name_file_output[i] = name_file[i];
	}
	name_file_output[i] = '\0';
	
	output = fopen(name_file_output,"wb");
	
	unsigned short int size_tree = 0;
	uc byte1, byte2, aux, trash;
	fscanf(input, "%c%c", &byte1, &byte2);
	aux = byte1 << 3;
	size_tree = aux;
	size_tree <<= 5;
	size_tree = size_tree | byte2;
	trash = byte1 >> 5;
	Node *tree = NULL;
	tree = create_tree_descompact(tree, input);
	lli number_bytes = number_of_bytes(input);
	fseek(input, size_tree + 2, SEEK_SET);
	put_caracter_in_file(input,output,tree,number_bytes,trash);
	printf("File successfully descompressed\n");
}