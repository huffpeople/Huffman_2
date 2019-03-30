#ifndef compact_h
#define compact_h

#include "header.h"
#include "hash.h"
#include "tree.h"
#include "heap.h"

/*Para montarmos o cabeçalho, precisamos de 16 bits, sendo 3 reservados para o lixo, e o resto 
para a árvore, e como o lixo não pode ser maior que 6, sempre usaremos no max 3 bits, logo, no precisamos
de dar shift bit de 13 para a esquerda, com isso basta fazermos uma operação de "ou" para adicionar 
o tamanho da árvore, e então separamos novamente em dois bytes, para adicionar no arquivo*/
void header (FILE *output, unsigned short int trash, int size_tree);

/*Coloca o caminho da árvore no arquivo tratando quando uma folha for '*' e '\', para diferenciar-mos
de um nó que não seja folha para a descompactação*/
void put_tree_in_file (Node *tree, FILE *output);

/*Recurssão para percorrer a árvore verificando se for um nó folha e for um "*" ou "\"
devemos por definição incrementar o tamanho da árvore pois colocaremos um caracter "\" adicional*/
void tree_size (Node *tree, int *size_tree);

/*Inicializamos o array de frequências de caracteres com zero, e incrementamos
a frequencia de acordo com o que se recebe do arquivo*/
void read_frequency(int *frequency, FILE *input);

/*Função que recebe o bit atual e "seta" o novo bit na posição a ser adicionado*/
uc set_bit (uc  byte, int i);

/*Nessa função, usamos para compactar o arquivo, nela, precisamos do nosso novo mapeamento e de lermos o arquivo novamente,
então iremos percorrer e adicionar o novo mapeamento em bytes zerados, quando completamos um byte, mandamos para o arquivo.
Com o mapeamento, iremos do tamanho da mapeamento até o fim do byte.
Temos uma verificação para sabermos se sobrou lixo ou não. Verificamos se o bit está setado, dando shift bit de 
sua posição atual, se o numero da divisão por 2 for 1 ele está setado, caso contrario, não está*/
short int set_bits (HASH *hash_table, FILE *input, FILE *output);

/*Primeiro é criado a fila de prioridade, monta a árvore, recebemos o novo tamanho da árvore
definimos o novo mapeamento e é colocado em uma hash, separa dois bytes para o cabeçalho
coloca a árvore no arquivo e os novos bytes, depois cria-se o cabeçalho*/
void compact ();


#endif

