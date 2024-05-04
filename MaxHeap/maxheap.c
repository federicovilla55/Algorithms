#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

typedef struct {
    int* array;
    int size;
} MaxHeap;

MaxHeap* createMaxHeap() {
    MaxHeap* heap = NULL;
    heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if(heap == NULL){
        printf("error\n");
        return NULL;
    }
    heap->size = 0;
    heap->array = NULL;
    heap->array = (int*)malloc(SIZE * sizeof(int));
    if(heap->array == NULL){
        printf("error\n");
        return NULL;
    }
    int capacity = SIZE-2;
    while(capacity--) heap->array[capacity] = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;    
    *b = temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void maxHeapify(MaxHeap* heap, int index) {
    int max = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left] > heap->array[max])
        max = left;

    if (right < heap->size && heap->array[right] > heap->array[max])
        max = right;

    if (max != index) {
        swap(&heap->array[index], &heap->array[max]);
        maxHeapify(heap, max);
    }
}

void deleteElementHeap(MaxHeap* heap, int value) {
    int index = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->array[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return;
    }

    heap->array[index] = heap->array[heap->size - 1];
    heap->size--;

    maxHeapify(heap, index);
}

void insertHeap(MaxHeap* heap, int value) {
    if (heap->size == SIZE) {
        printf("MaxHeap is full...\n");
        return;
    }

    int index = heap->size;
    heap->array[index] = value;
    heap->size++;

    while (index != 0 && heap->array[index] > heap->array[(index - 1) / 2]) {
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int getMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("error\n");
        return -1;
    }
    return heap->array[0];
}

void freeMaxHeap(MaxHeap* heap) {
    if (heap != NULL) {
        if (heap->array != NULL) {
            free(heap->array);
        }
        free(heap);
    }
}

int main(){
    MaxHeap* heap = createMaxHeap();
    
    insertHeap(heap, 8);
    insertHeap(heap, 7);
    insertHeap(heap, 10);
    insertHeap(heap, 4);
    insertHeap(heap, 9);

    printf("Max element in heap: %d\n", getMax(heap));
    deleteElementHeap(heap, 10);
    printf("I've deleted an element...\n");
    printf("Max element in heap: %d\n", getMax(heap));
    freeMaxHeap(heap);
}