/* recursive function that uses the Quicksort algorithm to sort a vector of integers  */

#include<stdio.h>

#define N 10

void quicksort(int a[], int low, int high);
int split(int a[], int low, int high);

int main(){
	int arr[N], i;

	printf("Enter %d numbers to be sorted: ", N);
	
	for(i=0; i< N; i++)
		scanf("%d", &arr[i]);
	quicksort(arr, 0, N-1),

	printf("In sorted order: ");
	
	for(i=0; i<N; i++)
		printf("%d ", arr[i]);
	
	printf("\n");
	
	return 0;
}

void quicksort(int a[], int low, int high){
	int middle;

	if(low>= high) return;
	
	middle = split(a, low, high);
	quicksort(a, low, middle - 1);
	quicksort(a, middle +1, high);

}

int split(int a[],int low, int high){
	int part_element;
	part_element = a[low];
	for(;;){
		while(low < high && part_element <=a[high])
			high--;
		if(low >=high) break;
		a[low++] = a[high];

		while(low < high && a[low] <= part_element)
			low++;
		if(low >= high) break;
		a[high--] = a[low];
	}

	a[high] = part_element;

	return high;
}

/* This version of quicksort can be improved through:
 * - the use of a more efficient partitioning algorithm (median between the various elements);
 * - the use of a non-recursive version of the quicksort */
