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

void countFrequencies(const char*, int*);
Node* buildHuffmanTree(int*);
void createCodes(Node*, char*, int, char**);
void encodeString(const char*, char**, char*);
void saveHuffmanArq(const char*, Node*, const char*);
void readHuffmanArchive(const char*, Node**, char**);
void decodeString(Node*, const char*, char*);

#endif