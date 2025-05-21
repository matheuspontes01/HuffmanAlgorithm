#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdbool.h>

typedef struct _node {
    unsigned char ch;
    struct _node *left, *right;
    int freq;
} Node;

typedef struct {
    int size;
    int capacity;
    Node** array;
} MinHeap;

/**
 * Cria o novo nó da árvore de Huffman com o valor fornecido.
 * @param unsigned char caractere representado pelo nó
 * @param int frequência do caractere
 * @return Node* ponteiro do novo nó criado
 */
Node* createNode(unsigned char, int);

/**
 * Cria uma min-heap com uma capacidade fornecida.
 * @param int capacidade com número máximo de elementos na heap
 * @return MinHeap* ponteiro para a nova minHeap criada
 */
MinHeap* createMinHeap(int);

/**
 * Troca a posição dos dois nós.
 * @param Node** u ponteiro para o primeiro nó
 * @param Node** v ponteiro para o segundo nó
 */
void switchNodes(Node**, Node**);

/**
 * Mantém a propriedade de min-heap reorganizando a heap a partir de um índice.
 * @param MinHeap* heap ponteiro para a heap
 * @param int i índice a partir do qual a reorganização começa
 */
void minHeapify(MinHeap*, int);

/**
 * Insere um novo nó na min-heap.
 * @param MinHeap* ponteiro para heap
 * @return Node* ponteiro o nó com menor frequência
 */
void insertMinHeap(MinHeap*, Node*);

/**
 * Remove e retorna o nó com menor frequência.
 * @param MinHeap* ponteiro para a heap
 * @return ponteiro para o nó com menor frequência
 */
Node* getMinFromMinHeap(MinHeap*);

/**
 * Constrói uma min-heap a partir do array atual de nós.
 * @param MinHeap* ponteiro para heap
 */
void buildMinHeap(MinHeap*);

/**
 * Verifica se o nó é uma folha ou não.
 * @param Node* ponteiro para o nó
 * @return true se for folha, caso contrário é false
 */
bool isLeaf(Node*);

/**
 * Libera toda a árvore.
 * @param Node* raiz da árvore a ser removida
 */
void freeTree(Node*);

/**
 * Conta a frequência de cada caractere na string de entrada.
 * @param const char* ponteiro para o string de entrada
 * @param int* vetor (tamanho 256) de ponteiros onde serão armazenadas as frequências
 */
void countFrequencies(const char*, int*);

/**
 * Constrói a árvore de Huffman a partir do vetor de frequências.
 * @param int* vetor de inteiros contando as frequências de cada caractere
 * @return Node* ponteiro para a raiz da árvore de Huffman construída 
 */
Node* buildHuffmanTree(int*);

/**
 * Cria os códigos binários para cada caractere a partir de uma árvore de Huffman. 
 * @param Node* ponteiro para a raiz da árvore
 * @param char* Vetor temporário para armazenar o código atual (usado na recursão)
 * @param int profundidade atual da árvore (posição no vetor de código)
 * @param char** vetor de strings onde serão armazenados os códigos binários gerados
 */
void createCodes(Node*, char*, int, char**);

/**
 * Codifica a string de entrada utilizando os códigos de Huffman. 
 * @param const char* Ponteiro para a string de entrada
 * @param char** Vetor de string com os códigos binários de cada caractere
 * @param char* Ponteiro para a string onde será armazenada a codificação final
 */
void encodeString(const char*, char**, char*);

/**
 * Salva a árvore de Huffman e a string codificada em um arquivo
 * @param const char* Nome do arquivo onde os dados serão salvos
 * @param Node* Ponteiro para a raiz da árvore
 * @param const char* Ponteiro para a string codificada
 */
void saveHuffmanArq(const char*, Node*, const char*);

/**
 * Lê o arquivo com os dados da árvore de Huffman e reconstrói a árvore e a string codificada. 
 * @param const char* Nome do arquivo a ser lido
 * @param Node** Ponteiro da raiz da árvore que vai ser reconstruída
 * @param char** Ponteiro para a string onde será armazenada a codificação lida
 */
void readHuffmanArchive(const char*, Node**, char**);

/**
 * Decodifica a string codificada utilizando a árvore de Huffman. 
 * @param Node* ponteiro para a raiz da árvore
 * @param const char* ponteiro para a string codificada
 * @param char* ponteiro para a string onde será armazenada a mensagem decodificada
 */
void decodeString(Node*, const char*, char*);

#endif