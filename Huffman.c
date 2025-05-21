#include "Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHARACTERS 256

Node* createNode(unsigned char ch, int freq) {
    Node* node = malloc(sizeof(Node));
    if (node) {
        node->ch = ch;
        node->left = NULL;
        node->right = NULL;
        node->freq = freq;
    }
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = malloc(sizeof(MinHeap));
    if (minHeap) {
        minHeap->size = 0;
        minHeap->capacity = capacity;
        minHeap->array = malloc(capacity * sizeof(Node*));
    }

    return minHeap;
}

void switchNodes(Node** u, Node** v) {
    Node* temp = *u;
    *u = *v;
    *v = temp;
}

void minHeapify(MinHeap* heap, int i) {
    int smaller = i, left = 2*i + 1, right = 2*i + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smaller]->freq) {
        smaller = left;
    }

    if (right < heap->size && heap->array[right]->freq < heap->array[smaller]->freq) {
        smaller = right;
    }

    if (smaller != i) {
        switchNodes(&heap->array[i], &heap->array[smaller]);
        minHeapify(heap, smaller);
    }
}

void insertMinHeap(MinHeap* heap, Node* node) {
    int i = heap->size++;
    while (i && node->freq < heap->array[(i-1) / 2]->freq) {
        heap->array[i] = heap->array[(i-1)/2];
        i = (i-1)/2;
    }
    heap->array[i] = node;
}

Node* getMinFromMinHeap(MinHeap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    minHeapify(heap, 0);
    return temp;
}

void buildMinHeap(MinHeap* heap) {
    int size = heap->size - 1;
    for (int i = (size-1)/2; i >= 0; i--) {
        minHeapify(heap, i);
    }
}

bool isLeaf(Node* node) {
    if (node->left == NULL && node->right == NULL) {
        return true;
    }
    return false;
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
