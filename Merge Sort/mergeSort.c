#include<stdio.h>
#include<limits.h>

#define DIM 15

void merge(int A[], int p, int q, int r);
void mergeSort(int A[], int p, int r);

int main(){
    int arr[DIM] = {30, 15, 27, 33, 22, 6, 18, 20, 14, 25, 1, 35, 2, 5, 3};
    int i;

    mergeSort(arr, 0, DIM);

    printf("Result: ");
    for(i=0; i<DIM; i++)
        printf(" %d ", arr[i]);

    return 0;
}

void merge(int A[], int p, int q, int r){
    int len1, len2, i, j;
    len1 = q - p;
    len2 = r - q;

    int left[len1+1], right[len2+1];

    for(i=0; i<len1; i++)
        left[i] = A[i+p];
    
    for(i=0; i<len2; i++)
        right[i]=A[i+q];

    left[len1] = INT_MAX;
    right[len2] = INT_MAX;

    i = 0;
    j = 0;

    while(p < r){
        if(left[i] < right[j]){
            A[p] = left[i];
            i++;
        }else{
            A[p] = right[j];
            j++;
        }
        p++;
    }
}

void mergeSort(int A[], int p, int r){
    if(p+1 < r){
        int q = (p + r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q, r);
        merge(A, p, q, r);
    }
}
