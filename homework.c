#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifndef _WIN32
#include<unistd.h> //sleep()
#else
#include<windows.h> //Sleep()
#endif



//inputstate notes:
//user== 1,2
//error== -1
//quit== -2



void printarr(int **arr, int row, int col, int user){ //print 2d array
#ifndef _WIN32
	printf("\x1b[2J");
#else
	system("cls");
#endif
	int count = 0;
	for (int i = 0; i<row; i++){
		for (int j = 0; j<col; j++){
			count++;
			if (arr[i][j] == 0) printf("%d\t", count);
			else if (arr[i][j] == 1) printf("O\t"); //player1==O
			else if (arr[i][j] == 2) printf("X\t"); //player2==X
		}
		if (i == 1) switch (user){
		case -1: printf("\t\tyou can't go there!"); break;
		default: printf("\t\tplayer%d's turn!", user); break;
		}
		printf("\n");

	}


}
/*printarr counts generationally
**printarr_alt counts by row*col */

void printarr_alt(int **arr, int row, int col, int user){ //print 2d array
#ifndef _WIN32
	printf("\x1b[2J");
#else
	system("cls");
#endif
	int count = 0;
	printf("\t");
	for (int i = 1; i <= row; i++) printf("%d\t", i);
	printf("\n");
	for (int i = 0; i<row; i++){
		printf("%d\t", i+1);
		for (int j = 0; j<col; j++){
			count++;
			if (arr[i][j] == 0) printf(".\t");
			else if (arr[i][j] == 1) printf("O\t"); //player1==O
			else if (arr[i][j] == 2) printf("X\t"); //player2==X
		}
		if (i == 1) switch (user){
		case -1: printf("\t\tyou can't go there!"); break;
		default: printf("\t\tplayer%d's turn!", user); break;
		}
		printf("\n");

	}


}

int advinput(){
	fflush(stdin); //flush any remaining cr
	
	char *input = (char *)calloc(1, sizeof(char));
	scanf("%s", input); //scanf address to string goes like this...
	if (input[0] == 'q') return 'q';
	int var1 = atoi(input);
	int var2 = 1;
	for (int i = 0; input[i]; i++){
		if (input[i] == 'x'){
			var2 = atoi(&input[i + 1]);
			break;
		}
	}
	return var1*var2;
}

typedef struct input_alt{
	int val1;
	int val2;
} input_alt;

input_alt *advinput_alt(){
	fflush(stdin); //flush any remaining cr
	input_alt *test = (input_alt *)calloc(1, sizeof(input_alt));
	char *input = (char *)calloc(1, sizeof(char));
	scanf("%s", input); //scanf address to string goes like this...
	if (input[0] == 'q'){
		test->var1 = 'q';
		return test;
	}
	test->var1 = atoi(input);
	test->var2 = 1;
	for (int i = 0; input[i]; i++){
		if (input[i] == 'x'){
			test->var2=atoi(&input[i + 1]);
			break;
		}
	}
	return test;
}

int userinput_alt(int **arr, int row, int col, int user){
	int result_r = row, result_c = col, max = row*col, min = 1;
	input_alt *pass;
	printf("player%d>>", user);
	pass = advinput_alt();
	//printf("%c %d", input, input);
#ifndef _WIN32
	sleep(1); //1sec
#else
	//Sleep(1000); //1sec
#endif
	if (pass->var1 == 'q') return -2;
	//input -= 48; //ascii 1 is 49 //we dont need this anymore
	if (pass->var1>max || pass->var1<min) return -1;
	if (pass->var2>max || pass->var2<min) return -1;

	//printf("%dx%d", result_r, result_c);
	if (arr[pass->var1][pass->var2] != NULL) return -1; //problem
	arr[pass->var1][pass->var2] = user;
	return 0;
}

int userinput(int **arr, int row, int col, int user){
	int input = NULL, result_r = row, result_c = col, max = row*col, min = 1;
	printf("player%d>>", user);
	input = advinput();
	//printf("%c %d", input, input);
#ifndef _WIN32
	sleep(1); //1sec
#else
	//Sleep(1000); //1sec
#endif
	if (input == 'q') return -2;
	//input -= 48; //ascii 1 is 49 //we dont need this anymore
	if (input>max||input<min) return -1;
	input--; //offset =input-1
	result_r = input / col;
	result_c = input % col;

	//printf("%dx%d", result_r, result_c);
	if (arr[result_r][result_c] != NULL) return -1; //problem
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

void printstatus(int **arr, int row, int col, int inputstate){
	printf("asdf");
	if (inputstate==-2) exit(0);
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

	int inputstate;
	for (;; switchuser++){ //mainloop

		user = switchuser % 2 + 1;
		printarr_alt(arr, row, col, user);
		for (; (inputstate = userinput(arr, row, col, user))!=0;){
			switch (inputstate){
			case -1: printarr_alt(arr, row, col, inputstate); break;
			case -2: printstatus(arr, row, col, inputstate); break;
			default:;
			}
			//printf("inputstate:%d", inputstate);
		}
	}

	return 0;
}