#define swap(x,y) { x = x + y; y = x - y; x = x - y; }
#define arrsize 12
#define arrcontent { 12, 11, 10 , 9, 8, 7, 6, 5, 4, 3, 2, 1}
#include<stdio.h>
void quicksort(int* A, int left, int right){

	for (int i = 0; i < arrsize; i++) printf("%d ", A[i]);
	printf("\n");

	int pivot = left;
	int low = left + 1;
	int high = right;

	int i = low, j = high;

	//low pointer loop
	while(i <= right){

		//A[low] > A[pivot]
		if (A[i] > A[pivot]){

			//high pointer loop
			while (A[j] > A[pivot]){	//A[high] < A[pivot]
				j--;
			}
			high = j;
			j--;

			low = i;

			//end if low and high pointers cross
			if (low > high){
				break;
			}

			//swap if no OOB
			if (low <= right && high >= left + 1)
				swap(A[low], A[high]);

		}

		i++;
	}

	//swap if high isnt OOB
	if (high >= left + 1){
		swap(A[high], A[pivot]);
		pivot = high;
	}

	//divide if not end
	if (left < pivot - 1) quicksort(A, left, pivot - 1);
	if (pivot + 1 < right) quicksort(A, pivot + 1, right);
}

int main(){

	int A[arrsize] = arrcontent;
	printf("before sort: ");
	for (int i = 0; i < arrsize; i++) printf("%d ", A[i]);
	printf("\nduring sort: \n");
	quicksort(A, 0, arrsize - 1);
	printf("after sort: ");
	for (int i = 0; i < arrsize; i++) printf("%d ", A[i]);
	return 0;
}