#ifndef hash_h
#define hash_h

#include "header.h"
#include "tree.h"

typedef struct element {
	short int size;
	unsigned short int bits;
}Element;

typedef struct hash_table {
	Element *table[256];
}HASH;

HASH *create_hash ();

/*Recebemos o novo mapeamento e adicionamos a hash, salvando o seu tamanho, pois
precisamos saber até onde o byte foi usado*/
void put_in_hash(HASH *hash_table, unsigned short int bits, int size_bits, void* item);

/*Define o novo mapeamento, caminhando pelo árvore, sendo 0 para esquerda e 1 para a direita
fazendo uma operação de shift bit de 1 para a esquerda pra "setarmos" zero quando para a esquerda,
e adicionamos 1 quando para direita*/
void define_new_bits (Node *tree, HASH *hash_table, int i, unsigned short int bits);

#endif

