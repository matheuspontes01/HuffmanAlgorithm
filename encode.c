#include "Huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARACTERS 256

void countFrequencies(const char* text, int freq[MAX_CHARACTERS]) {
    for (int i = 0; text[i] != '\0'; i++) {
        freq[(unsigned char) text[i]]++; // Incrementa a frequência do caractere atual
    }
}

Node* buildHuffmanTree(int freq[MAX_CHARACTERS]) {
    MinHeap* minHeap = createMinHeap(MAX_CHARACTERS); // Cria a min-heap

    // Cria nós para cada caractere com frequência > 0 e os insere na heap
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (freq[i] > 0) 
            insertMinHeap(minHeap, createNode((char) i, freq[i]));
    }

    // Combina os dois menores nós até restar apenas a raiz
    while (minHeap->size > 1) {
        Node* left = getMinFromMinHeap(minHeap);
        Node* right = getMinFromMinHeap(minHeap);
        Node* new = createNode('\0', left->freq + right->freq); // Nó interno
        new->left = left;
        new->right = right;
        insertMinHeap(minHeap, new);
    }

    return getMinFromMinHeap(minHeap); // Raiz da árvore Huffman
}

void createCodes(Node* root, char* code, int level, char* codes[MAX_CHARACTERS]) {
    if (root->left) {
        code[level] = '0';
        createCodes(root->left, code, level + 1, codes);
    }
    if (root->right) {
        code[level] = '1';
        createCodes(root->right, code, level + 1, codes);
    }
    if (isLeaf(root)) {
        code[level] = '\0'; // Finaliza a string
        codes[(unsigned char) root->ch] = strdup(code); // Copia código para tabela
    }
}

void encodeString(const char* text, char* codes[MAX_CHARACTERS], char* result) {
    result[0] = '\0'; // Inicializa a string codificada
    for (int i = 0; text[i] != '\0'; i++) { 
        strcat(result, codes[(unsigned char) text[i]]); // Concatena código
    }
}

void serializeTree(Node* root, FILE* arq) {
    if (root == NULL) return;
    if (isLeaf(root)) {
        fprintf(arq, "1%c", root->ch); // Nó folha: marcador '1' + caractere
    } else {
        fprintf(arq, "0"); // Nó interno: apenas marcador '0'
        serializeTree(root->left, arq);
        serializeTree(root->right, arq);
    }
}

void saveHuffmanArq(const char* way, Node* root, const char* encodedString) {
    FILE* archive = fopen(way, "w");
    if (!archive) {
        perror("Erro ao abrir o arquivo\n");
        return;
    }
    serializeTree(root, archive); // Escreve a arvore no arquivo
    fprintf(archive, "\n%s", encodedString); // Escreve a string codificada
    fclose(archive);
}