#include<stdio.h>
#include<stdlib.h>

int **allocarr(int **arr, int row, int col) {
	int i;
	/*arr = calloc(row, sizeof(int *)); /*create a row of pointers*/

	arr = calloc(row, sizeof * arr); /*sizeof variable lets the compiler deduce the type*/
	for (i = 0; i<row; i++) {
		arr[i] = (int *)calloc(col, sizeof(int));


	}

	return arr;
}

void freearr(int **arr, int row, int col) {
	int i;
	for (i = 0; i<row; i++) free(arr[i]);
	free(arr);


}


void generate(int **arr, int n, int row, int col) {
	int i, j, k, l;
	/*row*/
	l = 0;
	for (i = 0; i < n; i++) {
		arr[row][i]++;

	}
	/*col*/
	for (i = 0; i < n; i++) {
		arr[i][col]++;

	}
	/*diagonal*/
	for (i = 0; i < n; i++) {
		
		if (row > col) {
			if ((row - col + i)>(n - 1)) break;
			arr[row - col + i][col - col + i]++;
		}
		else {
			if ((col - row + i)>(n - 1)) break;
			arr[row - row + i][col - row + i]++;
		}
	}
	/*reverse-diagonal*/
	for (i = 0; i < n; i++) {
		if (row > (n - 1 - col)) {
			if ((row - (n - 1 - col) + i)>(n - 1)) break;
			arr[row - (n - 1 - col) + i][col + (n - 1 - col) - i]++;
		}
		else {
			if ((col + row - i)< 0) break;
			arr[row - row + i][col + row - i]++;
		}
	}

}

void gen_start(int **arr, int n, int *count) {
	int i, j, k, l;
	static int row_count = 0;

	/*if nothing exists == first start*/
	k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (arr[i][j]) break;
			else k++;

		}
	}
	if (k == n*n) {
		generate(arr, n, 0, row_count++);
		return;

	}
	
	/*after start*/

	




}


void checkinput(int argc, char **argv) {
	/*check input*/
	if (argc != 2) {
		fprintf(stderr, "N not specified!\n");
		exit(1);
	}
	if (!atoi(argv[1])) {
		fprintf(stderr, "N must be an integer!\n");
		exit(1);
	}

}

int main(int argc, char **argv) {
	/*init*/
	int n=0;
	int queen = 0;
	int count = 0;
	int **arr = NULL;
	int i, j, k, l;
	
	checkinput(argc, argv);
	n = atoi(argv[1]);

	arr = allocarr(arr, n, n);

	generate(arr, n, 2, 3);

	gen_start(arr, n, &count);

	/*test*/

	for (i = 0; i < n; i++) {
		printf("\n\n");
		for (j = 0; j < n; j++) {
			printf("\t%d", arr[i][j]);
		}
	}
	getchar();

	/*test*/


	freearr(arr, n, n);



	return 0;

}