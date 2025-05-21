#include "Huffman.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Node* deserializeTree1(FILE *archive) {
    int c = fgetc(archive);
    if (c == EOF) return NULL;

    if (c == '1') {
        char character = fgetc(archive);
        return createNode(character, 0); // Nó folha
    } else {
        Node* node = createNode('\0', 0); // Nó interno
        node->left = deserializeTree1(archive);
        node->right = deserializeTree1(archive);
        return node;
    }
    return NULL;
}

Node* deserializeTree(FILE *archive) {
    return deserializeTree1(archive); // Função intermediária
}

void decodeString(Node* root, const char* encodedString, char* result) {
    int pos = 0;
    Node* curr = root;
    while (*encodedString) {
        if (*encodedString == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (isLeaf(curr)){
            result[pos++] = curr->ch;
            curr = root; // Reinicia a partir da raiz
        }
        encodedString++;
    }
    result[pos] = '\0'; // Finaliza a string
}

void readHuffmanArchive(const char* way, Node** root, char** encodedString) {
    FILE* archive = fopen(way, "r");
    if (!archive) {
        perror("Erro ao ler o arquivo.\n");
        return;
    }

    *root = deserializeTree(archive); // Reconstrói a árvore

    int c;
    while ((c = fgetc(archive)) != '\n' && c != EOF); // Pula para a linha da string codificada

    size_t capacity = 1024;
    size_t size = 0;

    *encodedString = (char*)malloc(capacity); // Inicia buffer

    // Lê o restante da string codificada
    while ((c = fgetc(archive)) != EOF) {
        (*encodedString)[size++] = (char)c;
        if (size >= capacity) {
            capacity *= 2;
            *encodedString = (char*)realloc(*encodedString, capacity);
        }
    }
    (*encodedString)[size] = '\0'; // Finaliza a string

    fclose(archive);
}
