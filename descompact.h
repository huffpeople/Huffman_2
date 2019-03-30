#ifndef descompact_h
#define descompact_h

#include "header.h"
#include "tree.h"
#include "heap.h"

/*Por ser uma árvore de huffman, ao recriarmos a árvore, sabemos quando um nó é uma folha
pois será diferente de "*", mas preciamos verificar se é realmente o caracter "*" na folha ou 
um "\", que foi definido para diferenciação*/
Node *create_tree_descompact (Node *tree, FILE *input);

/*Função para verificar a quantidade de bytes no arquivo, para na descompactação, sabermos
onde é o ultimo byte está e através do lixo do cabeçalho sabermos onde parar*/
lli number_of_bytes (FILE *input);

/*Função que recebe o byte atual e verifica em uma determinada posição se ele está "setado"*/
int is_bit_i_set (uc byte, int i);

Node* put_in_file (FILE *output, Node *tree_aux, Node *tree, int i, uc byte);

/*Função para criarmos o arquivo original, onde a partir dos bytes compactados verificamos bit a bit, e usamos uma
árvore auxiliar para percorremos até chegar em uma folha e adicionar ao arquivo, e no ultimo byte, se tivermos lixo
temos uma condição para trata-lo, e para verificarmos se é o ultimo byte, basta retirar-mos -1 da quantidade de bytes*/
void put_caracter_in_file (FILE *input, FILE *output, Node *tree, lli number_bytes, unsigned short int trash);

/*Primeiramente recebemos os dois bytes que são o tamanho da árvore e o lixo. Como são apenas 3 bits para
o lixo, e o resto para o tamanho da arvore, então separamos os dois bytes recebidos para o lixo e o tamanho 
da árvore*/
void descompact();

#endif