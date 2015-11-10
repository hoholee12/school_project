#include<stdio.h>

int main() {

	char *arr = malloc(14); /*(2byte unicode)*(6 characters)+(ascii spacebar)+(char null)==14bytes */
	strcpy(arr, "한국어 테스트");
	char arr2[14] = "한국어 테스트";


	printf("%s\n%s\n", arr, arr2);
	free(arr);


	return 0;
}