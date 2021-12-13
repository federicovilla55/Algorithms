/* The counting sort algorithm is an algorithm 
 * for sorting that is based on keys (small positive
 * integers).
 * Has a time complexity of O(n + k), where k is the range 
 * of the non negative integer keys. 
 * This algorithm isn't a comparison sort, it finds, for
 * every array element the number of elements less greater than it
 * and with this information inserts the element in the position
 * of the output array */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define DIM 1000
#define NUM_ELEMENTS 100

void countingSort(int a[], int b[], int k);

int main(){
    int arr[DIM], ord[DIM];
    int i, max;
    max = INT_MIN;

    printf("Insert %d elements: ", NUM_ELEMENTS);
    for(i=0; i<NUM_ELEMENTS; i++){
        scanf("%d", &arr[i]);
        if(max < arr[i])
            max = arr[i];
    }

    countingSort(arr, ord, max);

    printf("List ordered: ");
    for(i=0; i<NUM_ELEMENTS; i++)
        printf("%d ", ord[i]);

    printf("\n");
    return 0;
}

void countingSort(int a[], int b[], int k){
    int i, j, *c;
    c = malloc(sizeof(int) * k);
    for(i=0; i<k; i++){
        *(c+i) = 0;
    }
    for(j=0; j<NUM_ELEMENTS; j++){
        *(c + a[j]) = *(c + a[j]) + 1;
    }
    for(i=0; i<=k; i++){
        *(c+i) = *(c+i) + *(c+i-1);
    }
    for(j=NUM_ELEMENTS; j>=0; j--){
        b[c[a[j]]-1] = a[j];
        *(c+a[j]) = *(c + a[j]) - 1;
    }
}
