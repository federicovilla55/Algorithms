/* Implementation of the Insertion Sort*/

#include<stdio.h>
#define N 30

void insertionSort(int a[]);

int main(){
    int i, v[10];

    printf("Insert %d numbers to be sorted: ", N);
    for(i=0; i<N; i++){
        scanf("%d", &v[i]);
    }

    insertionSort(v);

    printf("Sorted elements: ");
    for(i=0; i<N; i++)
        printf("%d ", v[i]);
    printf("\n");

    return 0;

}

void insertionSort(int a[]){
    int i, j, key;

    for(i=1; i<N; i++){
        key = a[i];
        j = i - 1;
        while(j>=0 && a[j]>key){
            a[j+1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }

}

/* It's worst case performance is O(n^2), equal to its average performance */
