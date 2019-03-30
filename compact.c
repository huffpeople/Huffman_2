#include "compact.h"


void header (FILE *output, unsigned short int trash, int size_tree) {
	
	unsigned short int trash_size_tree = 0;
	trash <<= 13;
	trash_size_tree = trash | size_tree;
	uc byte1, byte2;
	byte1 = trash_size_tree >> 8;
	byte2 = trash_size_tree;
	rewind(output);
	fprintf(output, "%c%c",byte1,byte2);
	fclose(output);
}

void put_tree_in_file (Node *tree, FILE *output) {

	if (tree == NULL) {
		return;
	}
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

void tree_size (Node *tree, int *size_tree) {

	if (tree == NULL) {
		return;
	} else {
		if (tree->left == NULL && tree->right == NULL) {
			if(tree->item == '*' || tree->item == '\\') {
				*size_tree += 1;
			}
		}
		*size_tree += 1;
		tree_size(tree->left, size_tree);
		tree_size(tree->right, size_tree);
	}	
}

void read_frequency(int *frequency, FILE *input) {
    int i;
    for(i = 0; i < 256; i++){
        frequency[i] = 0;
    }
    uc caracter = 0;
	while (fscanf(input, "%c",&caracter) != EOF) {
        frequency[caracter] += 1;
    }
	fclose(input);
}

uc set_bit (uc byte, int i) {
	uc mask = 1 << i;
	return mask | byte;
}

short int set_bits (HASH *hash_table, FILE *input, FILE *output) {
	uc caracter;
	uc byte = 0;
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

void compact () {
    FILE *input;
    FILE *output;
    char name_file[100];
    
    printf("File name to compress: \n");
    printf("===> ");
    scanf("%s",name_file);
    
    input = fopen(name_file,"rb");
    
    if (input == NULL) {
        printf("Invalid file\n");
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
    uc byte = 0;
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
	printf("File successfully compressed\n");
}