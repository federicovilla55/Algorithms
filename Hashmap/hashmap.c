#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHMAP_SIZE 640000

typedef struct HashmapNode {
    int key;
    int value;
    struct HashmapNode* next;
} HashmapNode;

typedef struct HashMap {
    HashmapNode* table[HASHMAP_SIZE];
} HashMap;

HashMap* createHashMap() {
    HashMap* hashMap = (HashMap*)malloc(sizeof(HashMap));
    if(hashMap == NULL){
        printf("errore\n");
        return NULL;
    }
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        hashMap->table[i] = NULL;
    }
    return hashMap;
}

HashMap* hashMap = NULL;

int hashFunction(int key) {
    return key % HASHMAP_SIZE;
}

void insertHash(int key, int value) {
    int index = hashFunction(key);

    HashmapNode* node = (HashmapNode*)malloc(sizeof(HashmapNode));
    if(node == NULL){
        printf("errore\n");
        return;
    }
    node->key = key;
    node->value = value;
    node->next = NULL;

    if (hashMap->table[index] == NULL) {
        hashMap->table[index] = node;
    } else {
        HashmapNode* currentNode = hashMap->table[index];
        while (currentNode->next) currentNode = currentNode->next;
        currentNode->next = node;
    }
}

HashmapNode *getHash(int key) {
    HashmapNode* currentNode = hashMap->table[hashFunction(key)];
    while (currentNode) {
        if (currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

void removeKey(int key) {
    int tmp = hashFunction(key);

    HashmapNode* currentNode = hashMap->table[tmp];
    HashmapNode* prevNode = NULL;

    while (currentNode) {
        if (currentNode->key == key) {
            if (prevNode == NULL) {
                hashMap->table[tmp] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            free(currentNode);
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

void updateHash(int key, int value) {
    int index = hashFunction(key);

    HashmapNode* current = hashMap->table[index];

    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
}


int main(){
    printf("Inserting values into the Hashmap:\n");
    hashMap = createHashMap();

    insertHash(0, -1);
    insertHash(88, 8);
    insertHash(99, 9);

    printf("%d\n", getHash(88)->value);

    removeKey(88);

    if(getHash(88)==NULL){
        printf("Element removed.\n");
    }else{
        printf("Key 88 not found...\n");
    }

}