#ifndef DESCOMPACT_H
#define DESCOMPACT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hash.h"
#include "compact.h"

Node *create_tree_descompact (Node *tree, FILE *input)
{
    char item;
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

unsigned long long int number_of_bytes (FILE *input)
{
	unsigned long long int count = 0;
	unsigned char byte;
	while (fscanf(input,"%c", &byte) != EOF) {
		count += 1;
	}
	return count;
  }

int is_bit_i_set (unsigned char byte, int i) {
	unsigned char mask = 1 << i;
	return mask & byte;
}

void put_caracter_in_file (FILE *input, FILE *output, Node *tree, unsigned long long int number_bytes, unsigned short int trash)
{
	Node *tree_aux = tree;
	unsigned char byte;
	int i;
	for (int j = 0; j < number_bytes; j++) {
		fscanf(input,"%c", &byte);
		if ((j == number_bytes - 1) && trash != 0) {
			for (i = 7; i >= trash; i--) {
				if (is_bit_i_set(byte,i)) {
					tree_aux = tree_aux->right;
				} else {
					tree_aux = tree_aux->left;
				}
				if (tree_aux->left ==  NULL && tree_aux->right == NULL) {
					fprintf(output,"%c",tree_aux->item);
					tree_aux = tree;
				}
			}
			break;
		}

		for (i = 7; i >= 0; i--) {

			if (is_bit_i_set(byte,i)) {
				tree_aux = tree_aux->right;
			} else {
				tree_aux = tree_aux->left;
			}
			if (tree_aux->left ==  NULL && tree_aux->right == NULL) {
				fprintf(output,"%c",tree_aux->item);
				tree_aux = tree;
			}
		}
	}
	fclose(output);
	fclose(input);
}

void descompact()
{
	FILE *input;
	FILE *output;
	char name_file[100];
	printf("Nome do arquivo a ser descompactado: \n");
	scanf("%s", name_file);
	input = fopen(name_file,"rb");
	if (input == NULL ) {
		printf("Erro ao abrir o arquivo\n");
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
	unsigned char byte1, byte2, aux, trash;
	fscanf(input, "%c%c", &byte1, &byte2);
	aux = byte1 << 3;
	size_tree = aux;
	size_tree <<= 5;
	size_tree = size_tree | byte2;
	trash = byte1 >> 5;
	Node *tree = NULL;
	tree = create_tree_descompact(tree, input);
	unsigned long long int number_bytes = number_of_bytes(input);
	fseek(input, size_tree + 2, SEEK_SET);
	put_caracter_in_file(input,output,tree,number_bytes,trash);
	printf("Descompactado\n");
}

#endif
