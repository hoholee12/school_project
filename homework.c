/*homework.c - a tic-tac-toe game!
* Copyright (C) 2015  hoholee12@naver.com
*
* May be freely distributed and modified as long as copyright
* is retained.
* except for those motherfuckers who want to steal my homework without doing any hard work - go kill yourselves!!
*/




#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifndef _WIN32
#include<unistd.h> //sleep()
#else
#include<windows.h> //Sleep()
#endif


typedef struct scoredat{
	int score;
	int count;
}scoredat;


/*inputstate notes:
	user	==	1,2
	OOB		==	-1
	quit	==	-2
	typo	==	-3
	str		==	-4
*always sort with switch statement!!
*/


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

void printarr_alt(int **arr, int row, int col, int user, const char *str=""){ //print 2d array
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
		if (i == 1)
			switch (user){
			case -1: printf("\t\tyou can't go there!"); break;
			case -2: printf("\t\tHOW DID YOU GET HERE?! xDDD"); break;
			case -3: printf("\t\twhat?"); break;
			case -4: printf("\t\t%s", str); break;
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
	int val1 = atoi(input);
	int val2 = 1;
	for (int i = 0; input[i]; i++){
		if (input[i] == 'x'){
			val2 = atoi(&input[i + 1]);
			break;
		}
	}
	return val1*val2;
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
		test->val1 = 'q';
		return test;
	}
	test->val1 = atoi(input)-1; //offset-1
	test->val2 = -1; //offset-1
	for (int i = 0; input[i]; i++){
		if (input[i] == 'x'){
			test->val2=atoi(&input[i + 1])-1; //offset-1
			break;
		}
		
	}
	if (test->val2 == -1) test->val1=-3; //typo err
	return test;
}

int userinput_alt(int **arr, int row, int col, int user){
	int result_r = row, result_c = col, max = row-1, min = 0; //offset-1
	input_alt *pass;
	printf("player%d>>", user);
	pass = advinput_alt();
	//printf("%c %d", input, input);
#ifndef _WIN32
	sleep(1); //1sec
#else
	//Sleep(1000); //1sec
#endif
	switch (pass->val1){
	case 'q': return -2;
	case -3: return -3;
	}

	//input -= 48; //ascii 1 is 49 //we dont need this anymore
	if (pass->val1>max || pass->val1<min) return -1;
	if (pass->val2>max || pass->val2<min) return -1;

	//printf("%dx%d", result_r, result_c);
	if (arr[pass->val1][pass->val2] != NULL) return -1; //problem
	arr[pass->val1][pass->val2] = user;
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



/*
checkcondition properties:
-return 1 => player1 wins
-return 2 => player2 wins
-return 3 => its a tie!
-return 0 => nothing happens
how simple :3
*/

int checkcondition(int **arr, int row, int col){
	int i, j, bak, bad;
	//row
	for (i = 0; i < row; i++){
		bak = arr[i][0];
		bad = 0;
		for (j = 1; j < col; j++){
			if (arr[i][j] != bak){
				bad = 1;
				break; //not it
				
			}
		}
		if ((!bad)&&(bak!=0)) return bak;
	}
	//col
	for (i = 0; i < row; i++){
		bak = arr[0][i];
		bad = 0;
		for (j = 1; j < col; j++){
			if (arr[j][i] != bak){
				bad = 1;
				break; //not it

			}
		}
		if ((!bad) && (bak != 0)) return bak;
	}
	//diagonal
	bak = arr[0][0];
	bad = 0;
	for (i = 1; i < row; i++){
		if (arr[i][i] != bak){
			bad = 1;
			break;
		}
	}
	if ((!bad) && (bak != 0)) return bak;
	
	bak = arr[0][row-1];
	bad = 0;
	for (i = 1; i < row; i++){
		if (arr[i][row-i-1] != bak){
			bad = 1;
			break;
		}
	}
	if ((!bad) && (bak != 0)) return bak;

	//final sequence
	bad = 0;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (!arr[i][j]){
				bad = 1;
				break;
			}
		
		}
		if (bad == 1) break;
	}
	if (!bad) return 3; //tie
	
	return 0;
}

void printstatus(int inputstate, int totalplaytime = NULL, scoredat *player1 = NULL, scoredat *player2 = NULL, int user = NULL){
	switch (inputstate){
	case -2: printf("you have forfeited your turn! player%d wins!\n", 3 - user);
		if (3 - user == 1) player1->score++;
		else player2->score++;
		break;
	case -5: if (totalplaytime < 10 || totalplaytime>20){
					switch (totalplaytime % 10){
					case 1: printf("%dst round", totalplaytime); break;
					case 2: printf("%dnd round", totalplaytime); break;
					case 3: printf("%drd round", totalplaytime); break;
					default: printf("%dth round", totalplaytime); break;
					}
				}
			 else printf("%dth round", totalplaytime);
			printf(", player1 score=%d", player1->score);
			printf(", player2 score=%d", player2->score);

			if (player1->score > player2->score) printf("\nplayer1 won by +%d points", player1->score - player2->score);
			else if (player1->score == player2->score) printf("\nits a tie.");
			else printf("\nplayer2 won by +%d points", player2->score - player1->score);

			break;
	default:;

	}
	printf("\n\n");
}

int game(int row, int col, scoredat *player1, scoredat *player2, int totalplaytime){
	int **arr = NULL;
	arr = allocarr(arr, row, col);
	int switchuser = 0;
	int user = switchuser % 2 + 1; //pre

	int inputstate;
	for (;;){ //mainloop


		printarr_alt(arr, row, col, user);
		switch (checkcondition(arr, row, col)){
		case 1: printarr_alt(arr, row, col, -4, "player1 wins!"); return 1;
		case 2: printarr_alt(arr, row, col, -4, "player2 wins!"); return 2;
		case 3: printarr_alt(arr, row, col, -4, "its a tie!"); return 3;
		}
		for (; (inputstate = userinput_alt(arr, row, col, user)) != 0;){
			switch (inputstate){
			case -1: printarr_alt(arr, row, col, inputstate); break;
			case -2: printstatus(inputstate, totalplaytime, player1, player2, user); return 0;
			case -3: printarr_alt(arr, row, col, inputstate); break;
			default:;
			}
			//printf("inputstate:%d", inputstate);
		}
		switchuser++;
		user = switchuser % 2 + 1;
	}
	printf("go fuck yourselves, this code is broken!!!\n"); //you will never reach this line >:o
	exit(123);
	return 0;

}

/*game return info
	-return 1: player1 wins
	-return 2: player2 wins
	-return 3: its a tie*/

int main(int argc, char *argv[]){
	scoredat *player1 = (scoredat *)calloc(1, sizeof(scoredat));
	scoredat *player2 = (scoredat *)calloc(1, sizeof(scoredat));

	//scoredat test1 = {0}; //you can also init struct using this method, how nice!

	int row=3, col=3;
	if (argc == 2){
		row = atoi(argv[1]);
		col = atoi(xtarget(argv[1]));
	}
	if (col != row) col = row; //needed for square det
	//printf("%d x %d\n", row, col);
	char next;
	int totalplaytime;
	for (totalplaytime=1;;totalplaytime++){
		switch (game(row, col, player1, player2, totalplaytime)){
		case 1: player1->score++; break;
		case 2: player2->score++; break;
		case 3: break;//tie must be processed on before this...		
		}
		printstatus(-5, totalplaytime, player1, player2, NULL);
		printf("next round? Y/N:");
		fflush(stdin);
		next=getchar();
		switch (next){
		case 'y':;
		case 'Y':;
		case 10:break; //linefeed
		default: return 0; //quit game
		}

	}

	return 0;
}

/*TODO:
-still have scoredat->count lying around...maybe i can use it for internal game engine??
*/