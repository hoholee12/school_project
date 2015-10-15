#include<stdio.h>
#include<stdlib.h>


int **allocarr(int **arr, int row, int col){
	int i;
	arr=(int **)calloc(row, sizeof(int*/*create a row of int pointers*/));
	for(i=0; i<row; i++){
		arr[i]=(int *)calloc(col, sizeof(int));


	}

	return arr;
}

void freearr(int **arr, int row, int col){
	int i;
	for(i=0; i<row; i++) free(arr[i]);
	free(arr);


}

void printarr(int **arr, int row, int col){
	int i, j;
	for(i=0; i<row; i++){
		for(j=0;j<col;j++){
			printf("\t%d", arr[i][j]);
		}
		printf("\n\n");
	}


}



int main(){
	int **arr=NULL;
	arr=allocarr(arr, 3, 3);
	arr[0][0]=2;
	arr[2][2]=8;
	printarr(arr, 3, 3);
	freearr(arr,3, 3);
	return 0;
}
