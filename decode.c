#include "Huffman.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Reconstrói a árvore de Huffman a partir do arquivo
 * @param FILE Arquivo com a árvore serializada
 * @return Raiz da árvore reconstruída
 */
Node* deserializeTree1(FILE *archive) {
    int c = fgetc(archive); // Lê o caractere do arquivo
    if (c == EOF) return NULL; // Fim do arquivo

    if (c == '1') {
        // Se for nó folha, lê o caractere e cria o nó
        char character = fgetc(archive);
        return createNode(character, 0); 
    } else {
        // Se for nó interno, cria nó e continua recursivamente
        Node* node = createNode('\0', 0); 
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
    int pos = 0; // Posição atual na string de resultado
    Node* curr = root; // Começa pela raiz

    // Percorre cada bit da string codificada
    while (*encodedString) {
        // Vai para esquerda com '0' ou direita com '1'
        if (*encodedString == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        // Quando encontra uma folha, adiciona o caractere decodificado
        if (isLeaf(curr)){
            result[pos++] = curr->ch;
            curr = root; // Reinicia da raiz para o próximo caractere
        }
        encodedString++; // Vai para o próximo bit
    }
    result[pos] = '\0'; // Finaliza a string decodificada
}

void readHuffmanArchive(const char* way, Node** root, char** encodedString) {
    FILE* archive = fopen(way, "r"); // Abre o arquivo para leitura 
    if (!archive) {
        perror("Erro ao ler o arquivo.\n"); // Mostra o erro
        return;
    }

    *root = deserializeTree(archive); // Reconstrói a árvore

    int c;
    // Pula até a próxima linha (ignora a parte da árvore)
    while ((c = fgetc(archive)) != '\n' && c != EOF);

    size_t capacity = 1024; // Tamanho inicial do buffer
    size_t size = 0; // Tamanho atual

    *encodedString = (char*)malloc(capacity); // Aloca memória para a string

    // Lê o restante da string codificada
    while ((c = fgetc(archive)) != EOF) {
        (*encodedString)[size++] = (char)c;

        // Aumenta o buffer se necessário
        if (size >= capacity) {
            capacity *= 2;
            *encodedString = (char*)realloc(*encodedString, capacity);
        }
    }
    (*encodedString)[size] = '\0'; // Finaliza a string

    fclose(archive); // Fecha o arquivo
}
