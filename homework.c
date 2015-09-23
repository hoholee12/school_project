#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void printarr(int **arr, int row, int col, int user){ //print 2d array
	int count = 0;
	for (int i = 0; i<row; i++){
		for (int j = 0; j<col; j++){
			count++;
			if (arr[i][j] == 0) printf("%d\t", count);
			else if (arr[i][j] == 1) printf("O\t"); //player1==O
			else if (arr[i][j] == 2) printf("X\t"); //player2==X
		}
		if (i == 1) printf("\t\tplayer%d's turn!", user);
		printf("\n");

	}


}

int userinput(int **arr, int row, int col, int user){
	int input = NULL, result_r = row, result_c = col, max = row*col, min = 0;
	scanf("%d", &input);
	if (input>max) return 1;
	else if (input<min) return 1;
	input--; //offset =input-1
	result_r = input / col;
	result_c = input % col;

	//printf("%dx%d", result_r, result_c);
	if (arr[result_r][result_c] != NULL) return 1; //problem
	arr[result_r][result_c] = user;
	return 0;
}

int **allocarr(int **arr, int row, int col){ //allocate 2d array
	arr = (int **)calloc(row, sizeof(int)); //allocate row first
	for (int i = 0; i<row; i++) arr[i] = (int *)calloc(col, sizeof(int)); //allocate cols next

	return arr;
}


char *xtarget(char *arg){ //parse string
	int i;
	for (i = 0; arg[i]; i++){
		if (arg[i] == 'x') return &arg[i + 1];
	}
	return NULL;
}

int main(int argc, char *argv[]){
	int row=3, col=3;
	if (argc == 2){
		row = atoi(argv[1]);
		col = atoi(xtarget(argv[1]));
	}
	if (col != row) col = row; //needed for square det
	//printf("%d x %d\n", row, col);

	int **arr = NULL;
	arr = allocarr(arr, row, col);
	int switchuser = 0, user;

	
	for (;; switchuser++){ //mainloop
#ifndef _WIN32
		printf("\x1b[2J");
#else
		system("cls");
#endif
		user = switchuser % 2 + 1;
		printarr(arr, row, col, user);
		printf("player%d>>", user);
		for (; userinput(arr, row, col, user); printf("try again!>>"));


	}

	return 0;
}