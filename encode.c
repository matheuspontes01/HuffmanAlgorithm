#include "Huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARACTERS 256

void countFrequencies(const char* text, int freq[MAX_CHARACTERS]) {
    // Percorre a string de entrada, caractere por caractere
    for (int i = 0; text[i] != '\0'; i++) {
        freq[(unsigned char) text[i]]++; // Incrementa a frequência do caractere atual
    }
}

Node* buildHuffmanTree(int freq[MAX_CHARACTERS]) {
    MinHeap* minHeap = createMinHeap(MAX_CHARACTERS); // Cria a min-heap com capacidade para MAX_CHARACTERS elementos

    // Cria nós para cada caractere com frequência > 0 e os insere na heap
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (freq[i] > 0) 
            insertMinHeap(minHeap, createNode((char) i, freq[i]));
    }

    // Continua até restar apenas um nó da heap (raiz da árvore)
    while (minHeap->size > 1) {
        // Remove os dois nós com menor frequência
        Node* left = getMinFromMinHeap(minHeap);
        Node* right = getMinFromMinHeap(minHeap);
        
        // Cria um novo nó interno com frequência somada
        Node* new = createNode('\0', left->freq + right->freq); // Nó interno
        new->left = left; // Subárvore esquerda
        new->right = right; // Subárvore direita

        // Insere o novo nó na heap
        insertMinHeap(minHeap, new);
    }
    
    // Retonar o último nó restante, que é a raiz da árvore de Huffman 
    return getMinFromMinHeap(minHeap);
}

void createCodes(Node* root, char* code, int level, char* codes[MAX_CHARACTERS]) {
    // Verifica se existe a subárvore esquerda
    if (root->left) { 
        code[level] = '0'; // Adiciona '0' ao código
        createCodes(root->left, code, level + 1, codes);
    }
    if (root->right) { // Verifica se existe a subárvore direita
        code[level] = '1'; // Adiciona '1' ao código
        createCodes(root->right, code, level + 1, codes);
    }
    if (isLeaf(root)) { // Se o nó é um nó folha, salva o código gerado
        code[level] = '\0'; // Finaliza a string do código
        codes[(unsigned char) root->ch] = strdup(code); // Copia código para tabela
    }
}

void encodeString(const char* text, char* codes[MAX_CHARACTERS], char* result) {
    result[0] = '\0'; // Inicializa a string resultante vazia

    // Percore a string original
    for (int i = 0; text[i] != '\0'; i++) { 
        strcat(result, codes[(unsigned char) text[i]]); // Concatena código correspondente do caractere atual à string codificada
    }
}

/**
 * Serializa a árvore de Huffman para escrita em um arquivo
 * @param Node* raiz da árvore
 * @param FILE Arquivo onde a árvore será escrita
 */
void serializeTree(Node* root, FILE* arq) {
    if (root == NULL) return; // Caso base 
    if (isLeaf(root)) {
        // Nó folha: escreve '1' seguido do caractere
        fprintf(arq, "1%c", root->ch);
    } else {
        // Nó interno: escreve '0' e continua recursivamente
        fprintf(arq, "0");
        serializeTree(root->left, arq);
        serializeTree(root->right, arq);
    }
}

void saveHuffmanArq(const char* way, Node* root, const char* encodedString) {
    FILE* archive = fopen(way, "w"); // Abre arquivo para escrita
    if (!archive) {
        perror("Erro ao abrir o arquivo\n"); // Erro
        return;
    }
    serializeTree(root, archive); // Serializa a árvore no arquivo
    fprintf(archive, "\n%s", encodedString); // Escreve a string codificada
    fclose(archive); // Fecha o arquivo
}