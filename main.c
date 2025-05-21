#include "Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 256

int main() {
    // Encode
    char texto[1024];
    printf("Digite a string a ser codificada: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove o '\n' do final, se houver

    int frequencias[MAX_CHARACTERS] = {0};
    countFrequencies(texto, frequencias);

    Node* raiz = buildHuffmanTree(frequencias);

    char* codigos[MAX_CHARACTERS] = {0};
    char codigoTemp[256];
    createCodes(raiz, codigoTemp, 0, codigos);

    char* stringCodificada = (char*)malloc(strlen(texto) * 256);
    encodeString(texto, codigos, stringCodificada);

    saveHuffmanArq("saida.huff", raiz, stringCodificada);

    printf("String original: %s\n", texto);
    printf("String codificada: %s\n", stringCodificada);
    printf("Arquivo 'saida.huff' gerado com sucesso.\n");

    // Liberação de memória
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        free(codigos[i]);
    }
    free(stringCodificada);
    freeTree(raiz);

    // Decode
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