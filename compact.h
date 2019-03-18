#ifndef COMPACT_H
#define COMPACT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "hash.h"
#include "descompact.h"

Node *create_tree_compact(Heap *heap) {
    int i;
    Node *tree = NULL;
    for(i = heap->size; i >= 1; i--){
        tree = merge_nodes(heap);
    }
    return tree;
}

/*Encontrar o tamanho da árvore*/
void tree_size (Node *tree, int *size_tree) {

	if (tree == NULL) {
		return;
	} else {
		if (tree->left == NULL && tree ->right == NULL) {
			if(tree->item == '*' || tree->item == '\\') {
				*size_tree += 1;
			}
		}
		*size_tree += 1;
		tree_size(tree->left, size_tree);
		tree_size(tree->right, size_tree);
	}
}

/*Define o novo mapeamento, caminhando pelo árvore, sendo 0 para esquerda e 1 para a direita*/
void define_new_bits (Node *tree, HASH *hash_table, int i, unsigned short int bits) {

	if (tree->left == NULL && tree->right == NULL) {
		put_in_hash(hash_table, bits, i, tree->item);
		return;
	} else {
		bits <<= 1;
		define_new_bits(tree->left, hash_table, i + 1, bits);
		bits += 1;
		define_new_bits(tree->right, hash_table, i + 1, bits);
	}
}

/*Coloca o caminho da árvore no arquivo tratando quando uma folha for '*' e '\'*/
void put_tree_in_file (Node *tree, FILE *output) {

	if (tree->left == NULL && tree->right == NULL) {
		if (tree->item == '*') {
			fprintf(output,"\\*");
		} else if (tree->item == '\\') {
			fprintf(output,"\\\\");
		} else {
			fprintf(output,"%c",tree->item);
		}
		return;
	} else {
		fprintf(output,"%c",tree->item);
		put_tree_in_file(tree->left, output);
		put_tree_in_file(tree->right, output);
	}
}

unsigned char set_bit (unsigned char byte, int i) {

	unsigned char mask = 1 << i;
	return mask | byte;
}


short int set_bits (HASH *hash_table, FILE *input, FILE *output) {
	unsigned char caracter;
	unsigned char byte = 0;
	int i = 7;
	rewind(input);
	bool flag = false;
	while (fscanf(input,"%c", &caracter) != EOF) {
		for (int j = hash_table->table[caracter]->size -1 ; j >= 0; j--) {
			flag = false;
			if(i == -1) {
				fprintf(output,"%c",byte);
				i = 7;
				byte = 0;
				flag = true;
			}
			if((hash_table->table[caracter]->bits >> j) % 2 != 0) {
				byte = set_bit(byte, i);
			}
			i -= 1;
		}
	}
	short int trash = 0;
	if (flag == false) {
		fprintf(output,"%c",byte);
		trash = i + 1;
	}
	return trash;
}

void read_frequency(int *frequency, FILE *input)
{
    int i;
    /*Inicializar a frequência tudo com zero*/
    for(i = 0; i < 256; i++){
        frequency[i] = 0;
    }
    unsigned char caracter = 0;

    /*Receber as frequencias*/
	while (fscanf(input, "%c",&caracter) != EOF) {
        frequency[caracter] += 1;
    }
	fclose(input);
}

void header (FILE *output, unsigned short int trash, int size_tree)
{
	unsigned short int trash_size_tree = 0;
	/*dá shift bit no trash pra deixar o lixo no inicio*/
	trash <<= 13;
	/*faz uma operação de "ou" com o trash e o size_tree, para juntar e depois separar em dois bytes*/
	trash_size_tree = trash | size_tree;
	/*usa dois bytes para */
	unsigned char byte1, byte2;
	byte1 = trash_size_tree >> 8;
	byte2 = trash_size_tree;
	rewind(output);
	fprintf(output, "%c%c",byte1,byte2);
	fclose(output);
}

void compact ()
{
      FILE *input;
	  FILE *output;
      char name_file[100];

      printf("Nome do arquivo: \n");
      scanf("%s",name_file);

      input = fopen(name_file,"rb");

      if (input == NULL) {
          printf("Erro ao abrir o arquivo\n");
          return;
      }
      int frequency[256];
      read_frequency(frequency,input);
      Heap *heap1 = create_heap();
      int i;
      for (i = 0; i < 256; i++){
          if(frequency[i] != 0){
              Node *new_node = create_node(i,frequency[i]);
              enqueue(heap1, new_node);
          }
      }
      Node *tree = NULL;
      tree = create_tree_compact(heap1);

	  int size_tree = 0;
	  tree_size (tree, &size_tree);
	  HASH *hash_table = create_hash();
	  unsigned short bits = 0;
	  define_new_bits(tree,hash_table,0,bits);
	 unsigned char byte = 0;
	 char name_file2[100];
	 strcpy(name_file2,name_file);
	 strcat(name_file2,".huff");
	 output = fopen(name_file2,"wb");
	 fprintf(output,"%c%c",byte,byte);
	 put_tree_in_file(tree, output);
	 input = fopen(name_file,"rb");
	 unsigned short int trash;
	 trash = set_bits(hash_table,input,output);
	 header(output,trash,size_tree);
}

#endif
