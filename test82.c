#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>


int main() {
	int *arr;

	arr = malloc(10); /*10bytes allocated*/

	arr[0] = 123; /*4bytes*/
	arr[1] = 456; /*8bytes*/
	arr[2] = 789; /*12bytes == 2bytes corrupted*/
	
	printf("%d %d %d\n", arr[0], arr[1], arr[2]);
	free(arr); /*what?!*/



	return 0;

}