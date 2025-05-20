#include "Huffman.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Node* deserializeTree1(FILE *archive) {
    int c = fgetc(archive);
    if (c == EOF) return NULL;

    if (c == '1') {
        char character = fgetc(archive);
        return createNode(character, 0);
    } else {
        Node* node = createNode('\0', 0);
        node->left = deserializeTree1(archive);
        node->right = deserializeTree1(archive);
        return node;
    }
    return NULL;
}

Node* deserializeTree(FILE *archive) {
    return deserializeTree1(archive);
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
            curr = root;
        }
        encodedString++;
    }
    result[pos] = '\0';
}

void readHuffmanArchive(const char* way, Node** root, char** encodedString) {
    FILE* archive = fopen(way, "r");
    if (!archive) {
        perror("Erro ao ler o arquivo.\n");
        return;
    }

    *root = deserializeTree(archive);

    int c;
    while ((c = fgetc(archive)) != '\n' && c != EOF);

    size_t capacity = 1024;
    size_t size = 0;

    *encodedString = (char*)malloc(capacity);

    while ((c = fgetc(archive)) != EOF) {
        (*encodedString)[size++] = (char)c;
        if (size >= capacity) {
            capacity *= 2;
            *encodedString = (char*)realloc(*encodedString, capacity);
        }
    }
    (*encodedString)[size] = '\0';

    fclose(archive);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    char* encodedString = NULL;

    readHuffmanArchive("saida.huff", &root, &encodedString);

    if (root == NULL || encodedString == NULL) {
        fprintf(stderr, "Erro ao ler ou processar o arquivo de entrada.\n");
        return 1;
    }

    char* decodedString = malloc(strlen(encodedString) + 1); // aloca memória suficiente
    if (!decodedString) {
        perror("Erro ao alocar memória para string decodificada");
        free(encodedString);
        freeTree(root);
        return 1;
    }

    decodeString(root, encodedString, decodedString);

    printf("String codificada: %s\n", encodedString);
    printf("String decodificada: %s\n", decodedString);

    // Liberação de memória
    free(decodedString);
    free(encodedString);
    freeTree(root);

    return 0;
}
