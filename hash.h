#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct element {
	short int size;
	unsigned short int bits;
}Element;

typedef struct hash_table {
	Element *table[256];
}HASH;

HASH *create_hash ()
{
	HASH *new_hash = (HASH*)malloc(sizeof(HASH));
	int i = 0;
	for (i = 0; i < 256; i++) {
		new_hash->table[i] = NULL;
	}
	return new_hash;
}

/*Recebe o novo mapeamento e coloca na hash na posição do item*/
void put_in_hash(HASH *hash_table, unsigned short int bits, int size_bits, unsigned char item)
{
	Element *new_element = (Element*)malloc(sizeof(Element));
	new_element->bits = bits;
	new_element->size = size_bits;
	hash_table->table[item] = new_element;
}

#endif
