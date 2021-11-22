/* C implementation of the HEAPSORT algorithm 
 * The time complexity is O(n*log(n)) and it is an in-place algorithm */

#include<stdio.h>
#define DIM 10
int size;

void maxHeapify(int A[], int i);
void createMaxHeap(int A[]);
void heapsort(int A[]);

int main(){
	int i, A[DIM];
	
	printf("Fill and array of %d elements: ", DIM);
	for(i=0; i<DIM; i++)
		scanf("%d", &A[i]);
	
	heapsort(A);

	printf("Array Sorted with HEAPSORT: ");
	for(i=0; i<DIM; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}

void maxHeapify(int A[], int i){
	int leftChild, rightChild, max, tmp;
	rightChild = 2*(i+1);
	leftChild = rightChild - 1;
	if(leftChild < size && A[leftChild] > A[i]){
		max = leftChild;
	}else{
		max = i;
	}
	if(rightChild < size && A[rightChild] > A[max]){
		max = rightChild;
	}
	if(max != i){
		tmp = A[i];
		A[i] = A[max];
		A[max] = tmp;
		maxHeapify(A, max);
	}
}

void createMaxHeap(int A[]){
	int i;
	size = DIM;
	for(i=DIM/2-1; i >= 0; i--)
	       maxHeapify(A, i);	
}

void heapsort(int A[]){
	int i, tmp;
	createMaxHeap(A);
	for(i=DIM-1; i>=1; i--){
		tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;
		size--;
		maxHeapify(A, 0);
	}
}
