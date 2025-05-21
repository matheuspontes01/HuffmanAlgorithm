#include "Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHARACTERS 256

Node* createNode(unsigned char ch, int freq) {
    Node* node = malloc(sizeof(Node)); // Criando o nó
    if (node) { // Se a criação foi sucesso, insere as informações iniciais do nó
        node->ch = ch;
        node->left = NULL;
        node->right = NULL;
        node->freq = freq;
    }
    return node; // Retorna o nó
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = malloc(sizeof(MinHeap)); // Cria a Heap
    if (minHeap) {
        minHeap->size = 0;
        minHeap->capacity = capacity;
        minHeap->array = malloc(capacity * sizeof(Node*)); // Cria um array dessa heap com a capacidade passada no parâmetro
    }

    return minHeap; // Retorna a MinHeap
}

void switchNodes(Node** u, Node** v) {
    Node* temp = *u; // Nó temporário para não perder a informação do nó u, pois será substituido pelo nó v
    *u = *v;
    *v = temp;
}

void minHeapify(MinHeap* heap, int i) {
    int smaller = i; // De início, o menor é o próprio índice atual
    int left = 2*i + 1;  // Índice do filho esquerdo
    int right = 2*i + 2; // Índice do filho direito

    // Verifica se o filho esquerdo existe e é menor que o atual menor
    if (left < heap->size && heap->array[left]->freq < heap->array[smaller]->freq) {
        smaller = left;
    }

    // Verifica se o filho direito existe e é menor que o atual menor
    if (right < heap->size && heap->array[right]->freq < heap->array[smaller]->freq) {
        smaller = right;
    }

    // Se o menor não for o próprio nó, faz a troca e chama recursivamente
    if (smaller != i) {
        switchNodes(&heap->array[i], &heap->array[smaller]);
        minHeapify(heap, smaller); // Corrige de forma recursiva a subárvore
    }
}

void insertMinHeap(MinHeap* heap, Node* node) {
    int i = heap->size++; // Insere o nó no fim da heap, aumentando o tamanho

    // Sobe o nó enquanto sua frequência for menor que a do pai
    while (i && node->freq < heap->array[(i-1) / 2]->freq) {
        heap->array[i] = heap->array[(i-1)/2]; // Move o pai para baixo
        i = (i-1)/2; // Sobe o índice do pai
    }
    heap->array[i] = node; // Coloca o novo nó na posição correta
}

Node* getMinFromMinHeap(MinHeap* heap) {
    Node* temp = heap->array[0]; // Guarda o nó minimo
    heap->array[0] = heap->array[--heap->size]; // Move o último nó para a raiz e reduz o tamanho
    minHeapify(heap, 0); // Restaura a propriedade heap
    return temp; // retornar o nó removido
}

void buildMinHeap(MinHeap* heap) {
    int size = heap->size - 1;
    
    // Reorganiza a heap dos nós internos até a raiz
    for (int i = (size-1)/2; i >= 0; i--) {
        minHeapify(heap, i); // Garante a propriedade de min-heap para cada subárvore
    }
}

bool isLeaf(Node* node) {
    if (node->left == NULL && node->right == NULL) { // Se o nó nao tiver filho na esquerda e na direita, então é um nó folha
        return true;
    }
    return false; // Caso contrário, não é nó folha
}

void freeTree(Node* root) {
    if (root == NULL) // Se a raiz for nula, finalize a função
        return;

    // Senão, libera-se as sub-árvores esquerda e direita
    freeTree(root->left);
    freeTree(root->right);
    free(root); // Libera a raiz
}
