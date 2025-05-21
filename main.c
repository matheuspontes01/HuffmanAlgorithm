#include "Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 256

int main() {
    // Codificação
    char texto[1024]; // Declara um buffer para armazenar o texto de entrada

    printf("Digite a string a ser codificada: ");
    fgets(texto, sizeof(texto), stdin);

    texto[strcspn(texto, "\n")] = '\0'; // Remove o caractere '\n' ao final da string (se presente)

    int frequencias[MAX_CHARACTERS] = {0}; // Inicializa o vetor de frequências com zeros
    countFrequencies(texto, frequencias); // Conta quantas vezes cada caractere aparece no texto

    Node* raiz = buildHuffmanTree(frequencias); // Constrói a árvore de Huffman a partir das frequências

    char* codigos[MAX_CHARACTERS] = {0}; // Vetor que armazenará os códigos binários de cada caractere
    char codigoTemp[256]; // Buffer temporário para construir os códigos binários
    createCodes(raiz, codigoTemp, 0, codigos); // Preenche o vetor de códigos com base na árvore

    char* stringCodificada = (char*)malloc(strlen(texto) * 256); // Aloca memória para armazenar a string codificada
    encodeString(texto, codigos, stringCodificada); // Codifica a string original usando os códigos gerados

    saveHuffmanArq("saida.huff", raiz, stringCodificada); // Salva a árvore e a string codificada no arquivo

    printf("String original: %s\n", texto);
    printf("String codificada: %s\n", stringCodificada);
    printf("Arquivo 'saida.huff' gerado com sucesso.\n");

    // Liberação de memória dos códigos
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        free(codigos[i]);
    }
    free(stringCodificada);
    freeTree(raiz);

    // Decodificação
    Node* root = NULL; // Ponteiro para a árvore reconstruída
    char* encodedString = NULL; // Ponteiro para a string codificada lida do arquivo

    readHuffmanArchive("saida.huff", &root, &encodedString); // Lê a árvore e a string codificada do arquivo

    // Verifica se houve erro na leitura
    if (root == NULL || encodedString == NULL) {
        fprintf(stderr, "Erro ao ler ou processar o arquivo de entrada.\n");
        return 1;
    }

    // Aloca memória suficiente para armazenar a string decodificada
    char* decodedString = malloc(strlen(encodedString) + 1); 
    if (!decodedString) {
        perror("Erro ao alocar memória para string decodificada"); // Mensagem de erro em caso de falha
        free(encodedString);
        freeTree(root);
        return 1;
    }

    decodeString(root, encodedString, decodedString); // Decodifica a string usando a árvore reconstruída

    printf("String codificada: %s\n", encodedString);
    printf("String decodificada: %s\n", decodedString);

    // Liberação de memória
    free(decodedString);
    free(encodedString);
    freeTree(root);

    return 0;
}
