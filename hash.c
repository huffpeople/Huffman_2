#include "hash.h"

HASH *create_hash () {
	HASH *new_hash = (HASH*)malloc(sizeof(HASH));
	int i = 0;
	for (i = 0; i < 256; i++) {
		new_hash->table[i] = NULL;
	}
	return new_hash;
}

void put_in_hash(HASH *hash_table, unsigned short int bits, int size_bits, void* item) {

	Element *new_element = (Element*)malloc(sizeof(Element));
	new_element->bits = bits;
	new_element->size = size_bits;
	hash_table->table[(uc)(item)] = new_element;
}

void define_new_bits (Node *tree, HASH *hash_table, int i, unsigned short int bits) {
	
	if (tree == NULL) {
		return;
	}
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