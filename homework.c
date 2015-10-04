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
#include<string.h>

typedef struct scoredat{
	int score;
	int count;
}scoredat;
typedef struct Option{
	int swap;
	int playa2;
} Option;

/*inputstate notes:
user	==	1,2
****************** lets not mix things up...
err:
OOB		==	-1
quit	==	-2
typo	==	-3
str		==	-4
*always sort with switch statement!!
*/

//non _alt versions are all deprecated and should not be used!!
/*
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
*/
/*printarr counts generationally
**printarr_alt counts by row*col */

void printarr_alt(int **arr, int row, int col,
	int user,
	int err, //just one user variable is not enough
	const char *str,
	Option *option
	){
#ifndef _WIN32
	printf("\x1b[2J\x1b[0;0H");
#else
	system("cls");
#endif
	int player1_count = 0, player2_count = 0, i, j;
	printf("\t");
	for (i = 1; i <= row; i++) printf("%d\t", i);



	//input option menu here, three letters each!
	printf("\tOptions: ");
	if (option->swap == 1) printf("SWP ");
	if (option->playa2 == 1) printf("AUTO ");
	printf("\n");

	//preprocessing for player1_count, player2_count
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			switch (arr[i][j]){
			case 0: break;
			case 1: player1_count++; break;
			case 2: player2_count++; break;
			}
		}
	}

	//mainloop output
	printf("\n");
	for (i = 0; i<row; i++){
		printf("%d\t", i + 1);
		for (j = 0; j<col; j++){
			switch (arr[i][j]){
			case 0: printf(".\t"); break;
			case 1: printf("O\t"); break;
			case 2: printf("X\t"); break;
			}
		}
		if (i == 0){
			printf("\tplayer1=%d/%d  player2=%d/%d  total=%d/%d",
				player1_count, row*row/2, player2_count, row*row/2, player1_count + player2_count, row*row);
		}
		if (i == 1){
			if (option->playa2 == 1 && user == 2){
				switch (err){
				case -4: printf("\t\t%s", str); break;
				default: printf("\t\tplayer%d's turn!", user); break;
				}
			
			}
			else{
				switch (err){
				case -1: printf("\t\tyou can't go there!"); break;
				case -2: printf("\t\tHOW DID YOU GET HERE?! xDDD"); break;
				case -3: printf("\t\twhat?"); break;
				case -4: printf("\t\t%s", str); break;
				default: printf("\t\tplayer%d's turn!", user); break;
				}
			}
		}
		printf("\n\n");

	}


}
/*
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
*/
typedef struct input_alt{
	int val1; //y row
	int val2; //x col
} input_alt;

int dividenum(int row){
	int count = 0, i;
	for (i = 1; row / i; i *= 10) count++;
	return count;
}

int advinput_alt(
	input_alt *pass,
	int row, int col
	){
	int i;
	fflush(stdin); //flush any remaining cr
	char *input = calloc(dividenum(row) * 2 + 2/*'+'+NULL*/, sizeof(char));	//char input[size] wont work if 'size' is not available on compile time!!
	input = realloc(input, 0xFFF); //fail proof *** i dont need to initialize the rest of the appending memory
	//you should use heap memory for that.
	//dont use more than already assigned, free() will complain about corrupted heap memory!!
	gets(input); //i want to include spaces too.
	if (input[0] == 'q'){
		pass->val1 = 'q';
		return 0;
	}
	pass->val1 = atoi(input) - 1; //offset-1
	pass->val2 = -1; //offset-1

	for (i = 0; input[i]; i++){
		if (input[i] == 'x'){
			pass->val2 = atoi(&input[i + 1]) - 1; //offset-1
			break;
		}

	}
	if (pass->val2 == -1) pass->val1 = -3; //typo err
	free(input);
	return 0;
}

int userinput_alt(int **arr, int row, int col,
	int user,
	Option *option
	){
	int i, result_r = row, result_c = col, max = row - 1, min = 0; //offset-1
	input_alt pass = { 0 };
	if (option->playa2 == 1 && user == 2){
		printf("player2 is thinking");
		for (i = 0; i < 3; i++){
			printf(".");
#ifdef _WIN32
			Sleep(200); //0.2 seconds
#else
			fflush(stdout);
			usleep(200000);
#endif
		}
		if (player2engine(&pass, arr, row, col, option) == -1){
			fprintf(stderr, "player2engine() crashed!!"); //exception error
			abort();
		}
	}
	else{
		printf("player%d>>", user);
		advinput_alt(&pass, row, col);
	}
#ifdef _WIN32
	//Sleep(200); //0.2 seconds
#else
	//fflush(stdout);
	//usleep(200000);
#endif
	switch (pass.val1){
	case 'q': return -2;
	case -3: return -3;
	}

	//input -= 48; //ascii 1 is 49 //we dont need this anymore
	if (pass.val1>max || pass.val1<min) return -1;
	if (pass.val2>max || pass.val2<min) return -1;

	//this is where you can swap row & col, default should be val1=row, val2=col
	if (option->swap == 1&&user!=2){
		if (arr[pass.val2][pass.val1] != 0) return -1; //problem
		arr[pass.val2][pass.val1] = user;
	}
	else{
		if (arr[pass.val1][pass.val2] != 0) return -1; //problem
		arr[pass.val1][pass.val2] = user;
	}
	return 0;
}
/*
int userinput(int **arr, int row, int col, int user){
int input = NULL, result_r = row, result_c = col, max = row*col, min = 1;
printf("player%d>>", user);
input = advinput();
//printf("%c %d", input, input);
#ifndef _WIN32
//sleep(1); //1sec
#else
//Sleep(1000); //1sec
#endif
if (input == 'q') return -2;
//input -= 48; //ascii 1 is 49 //we dont need this anymore
if (input>max || input<min) return -1;
input--; //offset =input-1
result_r = input / col;
result_c = input % col;

//printf("%dx%d", result_r, result_c);
if (arr[result_r][result_c] != 0) return -1; //problem
arr[result_r][result_c] = user;
return 0;
}
*/
int **allocarr(int **arr, int row, int col){ //allocate 2d array
	int i;
	arr = calloc(row, sizeof(int)); //allocate row first
	for (i = 0; i<row; i++) arr[i] = calloc(col, sizeof(int)); //allocate cols next

	return arr;
}

void freearr(int **arr, int row, int col){ //free all memory from 2d array
	int i;
	for (i = 0; i < row; i++) free(arr[i]);
	free(arr);

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
		if ((!bad) && (bak != 0)) return bak;
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

	bak = arr[0][row - 1];
	bad = 0;
	for (i = 1; i < row; i++){
		if (arr[i][row - i - 1] != bak){
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

//*****************************************TODO

int quickcheck(int **arr, int row, int col){
	int **test = NULL;
	test=allocarr(test, row, col);
	
	
	checkcondition(arr, row, col);
	return 0;
}


//*****************************************TODO

void printstatus(
	int inputstate,
	int totalplaytime,
	scoredat *player1,
	scoredat *player2,
	int user
	){
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

int game(int row, int col,
	scoredat *player1,
	scoredat *player2,
	int totalplaytime,
	int *switchuser,
	Option *option
	){
	int **arr = NULL;
	arr = allocarr(arr, row, col);
	int user = *switchuser % 2 + 1; //pre

	int inputstate;
	for (;;){ //mainloop


		printarr_alt(arr, row, col, user, 0, "", option);
		switch (checkcondition(arr, row, col)){
		case 1: printarr_alt(arr, row, col, user, -4, "player1 wins!", option); freearr(arr, row, col); return 1;
		case 2: printarr_alt(arr, row, col, user, -4, "player2 wins!", option); freearr(arr, row, col); return 2;
		case 3: printarr_alt(arr, row, col, user, -4, "its a tie!", option); freearr(arr, row, col); return 3;
		}
		for (; (inputstate = userinput_alt(arr, row, col, user, option)) != 0;){
			switch (inputstate){
			case -1: printarr_alt(arr, row, col, user, inputstate, "", option); break;
			case -2: printstatus(inputstate, totalplaytime, player1, player2, user); (*switchuser)++; freearr(arr, row, col); return 0;
			case -3: printarr_alt(arr, row, col, user, inputstate, "", option); break;
			default:;
			}
			//printf("inputstate:%d", inputstate);
		}
		(*switchuser)++; //no brackets will actually mean *(switchuser++) so be careful!!
		user = *switchuser % 2 + 1;
	}
	printf("go fuck yourselves, this code is broken!!!\n"); //you will never reach this line >:o
	exit(123);
	return 0;

}

/*game return info
-return 1: player1 wins
-return 2: player2 wins
-return 3: its a tie*/

void seed(){
	srand((unsigned)time(NULL));

}

//user defined getopt_struct
typedef struct getopt_struct{
	int on;
	char *optstr; //strcpy needs the address of it! not itself...
} getopt_struct;

void simplegetopt(
	int argc, char **argv,
	getopt_struct *iparam,
	getopt_struct *rparam,
	getopt_struct *hparam,
	getopt_struct *aparam
	){
	int i;
	for (i = 1; i<argc; i++){
		if (!strcmp(argv[i], "-i")){ //better to use this than switch for strings. hash is a nightmare!
			if (strlen(argv[i + 1])>0xFD){ fprintf(stderr, "buffer overflow!\n"); abort(); } //0xFE - "null terminator"
			iparam->on++;
			strcpy(iparam->optstr, argv[++i]);
		}
		else if (!strcmp(argv[i], "-r")){
			rparam->on++;
		}
		else if (!strcmp(argv[i], "-h")){
			hparam->on++;
		}
		else if (!strcmp(argv[i], "-a")){
			aparam->on++;
		
		}
	}

}

void help(int argc, char **argv,
	getopt_struct *iparam,
	getopt_struct *rparam,
	getopt_struct *hparam,
	getopt_struct *aparam
	){
	fprintf(stderr, "homework.c - a tic-tac-toe game!"
		"\nCopyright(C) 2015  hoholee12@naver.com"
		"\nUsage: %s -i [row]x[col] -r"
		"\n\t-i sets derterminant size by [row]x[col]"
		"\n\t-r reverses [row][col] input ingame\n\n", argv[0]);
	free(iparam->optstr);
	free(rparam->optstr);
	free(hparam->optstr);
	free(aparam->optstr);
	exit(0);
};






//*****************************************TODO
//the cpu will always be player2!
/*
return 0 => normal
return 1 => normal(won or lost)
return -1 => abnormal(undecided, crashed)
*/

int player2engine(
	input_alt *pass,
	int **arr, int row, int col,
	Option *option
	){
	//inform that nothings been touched
	pass->val1 = -1;
	pass->val2 = -1;



	//declare here
	int i, j, k, broken=0, prev_brain=3/*maximum*/, nostart = 0, startloc_x, startloc_y, bak, worse, minor_y = -1, minor_x = -1, wow=0, prev_wow=0;
	int final_offset = 1;


	//if start first, put at center
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[i][j]){
				nostart++;
				if (arr[i][j] == 1){
					startloc_y = i;
					startloc_x = j;
				}
			}
		}
	}
	if (!nostart){
		pass->val1 = row / 2;
		pass->val2 = col / 2;
		return 0;
	}
	//if start second, put right next to the player1, random direction.
	if (nostart == 1){
		for (;;){
			pass->val1 = startloc_y + (rand() % 3 - 1);
			pass->val2 = startloc_x + (rand() % 3 - 1);
			if ((pass->val1 >= 0 && pass->val1 <= row) && (pass->val2 >= 0 && pass->val2 <= row) && ((pass->val1 != startloc_y) || (pass->val2 != startloc_x))) break;
		}
		return 0;
	}
	

	//third step - offense
	/*
	3==row col diag combined
	2==two of these combined
	1==just one
	something like that...

	we want to have the number negative to win!
	*/



	int **brain = NULL;
	brain=allocarr(brain, row, col);
	//col
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[i][j] == 1){
				for (k = 0; k < col; k++) brain[i][k]++; //fill whole line
				break;
			}
			if (arr[i][j] == 2){
				for (k = 0; k < col; k++) brain[i][k]--; //fill whole line
				break;
			}
		}
	
	}
	//row
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[j][i] == 1){
				for (k = 0; k < col; k++) brain[k][i]++; //fill whole line
				break;
			}
			if (arr[j][i] == 2){
				for (k = 0; k < col; k++) brain[k][i]--; //fill whole line
				break;
			}
		}

	}
	//diagonal
	for (i = 0; i < row; i++){
		if (arr[i][i] == 1){
			for (k = 0; k < col; k++) brain[k][k]++; //fill whole line
			break;
		
		}
		if (arr[i][i] == 2){
			for (k = 0; k < col; k++) brain[k][k]--; //fill whole line
			break;

		}
	}
	//reverse-diagonal
	for (i = 0; i < row; i++){
		if (arr[i][row - i - 1] == 1){
			for (k = 0; k < col; k++) brain[k][row - k - 1]++; //fill whole line
			break;

		}
		if (arr[i][row - i - 1] == 2){
			for (k = 0; k < col; k++) brain[k][row - k - 1]--; //fill whole line
			break;

		}
	}


	//input to brain
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (brain[i][j]<prev_brain&&arr[i][j]==0){
				prev_brain = brain[i][j];
				pass->val1 = i;
				pass->val2 = j;
			}
		
		}
	
	}

	//defense
	//col
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ //one col loop
			if (arr[i][j] == 1) worse++;
			else if (arr[i][j] == 2){
				broken = 1;
				break;
			}
			else minor_x = j;
		}
		if (broken == 1);
		else if (worse >= row - 1){
			pass->val1 = i;
			pass->val2 = minor_x;
			printf("col %d %d ;;", pass->val1, pass->val2);
		}
	}
	//row
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ //one col loop
			if (arr[j][i] == 1) worse++;
			else if (arr[j][i] == 2){ 
				broken = 1;
				break; 
			}
			else minor_y = j;
		}
		if (broken == 1);
		else if (worse >= row - 1){
			pass->val1 = minor_y;
			pass->val2 = i;
			printf("row %d %d ;;", pass->val1, pass->val2);
		}
	}


	//diagonal
	worse = 0;
	broken = 0;
	for (i = 0; i < row; i++){
			if (arr[i][i] == 1) worse++;
			else if (arr[i][i] == 2){
				broken = 1;
				break;
			}
			else minor_x = i;
	}
	if (broken == 1);
	else if (worse >= row - 1){
		pass->val1 = minor_x;
		pass->val2 = minor_x;
		printf("diag %d %d ;;", pass->val1, pass->val2);
	}


	//reverse diag
	worse = 0;
	broken = 0;
	for (i = 0; i < row; i++){
		if (arr[i][row-i-1] == 1) worse++;
		else if (arr[i][row - i - 1] == 2){
			broken = 1;
			break;
		}
		else{
			minor_y = i;
			minor_x = row - i - 1;
		}
	}
	if (broken == 1);
	else if (worse >= row - 1){
		pass->val1 = minor_y;
		pass->val2 = minor_x;
		printf("rev diag %d %d ;;", pass->val1, pass->val2);
	}


	//final shot
	if (worse){
		//col
		for (i = 0; i < row; i++){
			worse = 0;
			broken = 0;
			for (j = 0; j < col; j++){ //one col loop
				if (arr[i][j] == 2) worse++;
				else if (arr[i][j] == 1){
					broken = 1;
					break;
				}
				else minor_x = j;
			}
			if (broken == 1);
			else if (worse >= row - 1){
				pass->val1 = i;
				pass->val2 = minor_x;
				printf("fcol %d %d ;;", pass->val1, pass->val2);
			}
		}
		//row
		for (i = 0; i < row; i++){
			worse = 0;
			broken = 0;
			for (j = 0; j < col; j++){ //one col loop
				if (arr[j][i] == 2) worse++;
				else if (arr[j][i] == 1){
					broken = 1;
					break;
				}
				else minor_y = j;
			}
			if (broken == 1);
			else if (worse >= row - 1){
				pass->val1 = minor_y;
				pass->val2 = i;
				printf("frow %d %d ;;", pass->val1, pass->val2);
			}
		}


		//diagonal
		worse = 0;
		broken = 0;
		for (i = 0; i < row; i++){
			if (arr[i][i] == 2) worse++;
			else if (arr[i][i] == 1){
				broken = 1;
				break;
			}
			else minor_x = i;
		}
		if (broken == 1);
		else if (worse >= row - 1){
			pass->val1 = minor_x;
			pass->val2 = minor_x;
			printf("fdiag %d %d ;;", pass->val1, pass->val2);
		}


		//reverse diag
		worse = 0;
		broken = 0;
		for (i = 0; i < row; i++){
			if (arr[i][row - i - 1] == 2) worse++;
			else if (arr[i][row - i - 1] == 1){
				broken = 1;
				break;
			}
			else{
				minor_y = i;
				minor_x = row - i - 1;
			}
		}
		if (broken == 1);
		else if (worse >= row - 1){
			pass->val1 = minor_y;
			pass->val2 = minor_x;
			printf("frev diag %d %d ;;", pass->val1, pass->val2);
		}
	}


	//print brain
	printf("\n");
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%d\t", brain[i][j]);
		}
		printf("\n");
	
	}

	Sleep(1000);
	//in case something fails...
	if (pass->val1 == -1 && pass->val2 == -1){
		pass->val1 = rand() % row;
		pass->val2 = rand() % row;
		printf("nothing to do...%d %d", pass->val1, pass->val2);
	}
	else printf("result...%d %d", pass->val1, pass->val2);
	getchar();

	/*

	//col
	for (i = 0; i < row; i++){
		worse = 0;
		wow = 0;
		for (j = 1; j < col; j++){ //one col loop
			if (!arr[i][j]){ //if no block
				minor_y = i;
				minor_x = j;
			}
			else if (arr[i][j] == 1){ //discovered p1 block
				worse++;
				break;
			
			}
			else if (arr[i][j] == 2) wow++;
		}
		if (worse==0){
			if (wow>prev_wow){ //compare
				pass->val1 = minor_y;
				pass->val2 = minor_x;
				prev_wow=wow;
				printf("col wow %d %d ;;", pass->val1, pass->val2);
			}
		}
	}
	//row
	for (i = 0; i < row; i++){
		worse = 0;
		wow = 0;
		for (j = 1; j < col; j++){ //one col loop
			if (!arr[j][i]){ //if no block
				minor_y = j;
				minor_x = i;
			}
			else if (arr[j][i] == 1){ //discovered p1 block
				worse++;
				break;

			}
			else if (arr[j][i] == 2) wow++;
		}
		if (worse == 0){
			if (wow>prev_wow){ //compare
				pass->val1 = minor_y;
				pass->val2 = minor_x;
				prev_wow = wow;
				printf("row wow %d %d ;;", pass->val1, pass->val2);
			}
		}
	}

	
	//diagonal
	bak = arr[0][0];
	worse = 0;
	wow = 0;
	for (i = 1; i < row; i++){
		if (!arr[i][i]){
			minor_y = i;
			minor_x = i;
		}
		else if (arr[i][i] == 1){ //discovered p1 block
			worse++;
			break;

		}
		else if (arr[i][i] == 2) wow++;
	}
	if (worse == 0){
		if (wow>prev_wow){ //compare
			pass->val1 = minor_y;
			pass->val2 = minor_x;
			prev_wow = wow;
			printf("diag wow %d %d ;;", pass->val1, pass->val2);
		}
	}
	
	//reverse diag
	bak = arr[0][row - 1];
	worse = 0;
	wow = 0;
	for (i = 1; i < row; i++){
		if (!arr[i][row - i - 1]){
			minor_y = i;
			minor_x = i;
		}
		else if (arr[i][row - i - 1] == 1){ //discovered p1 block
			worse++;
			break;

		}
		else if (arr[i][row - i - 1] == 2) wow++;
	}
	if (worse == 0){
		if (wow>prev_wow){ //compare
			pass->val1 = minor_y;
			pass->val2 = minor_x;
			prev_wow = wow;
			printf("rev diag wow %d %d ;;", pass->val1, pass->val2);
		}
	}

	Sleep(1000);
	//in case something fails...
	if (pass->val1 == -1 && pass->val2 == -1){
		pass->val1 = rand() % row;
		pass->val2 = rand() % row;
		printf("nothing to do...%d %d", pass->val1, pass->val2);
		Sleep(1000);
	}


	/*
	int minor_x = -1, minor_y = -1;

	for (i=0;i<row;i++){
		for (j = 0; j < row; j++){
			startloc_y = i;
			startloc_x = j;
			if (arr[i][j] == 2){
				for (minor_y = -1; minor_y < 2; minor_y++){
					for (minor_x = -1; minor_x < 2; minor_x++){
						if (arr[startloc_y + minor_y][startloc_x + minor_x] == 0){
							pass->val1 = startloc_y + minor_y;
							pass->val2 = startloc_x + minor_x;
							return 0;
						}
					}
				}
				if (minor_y==2&&minor_x==2) continue;//if no opening
			
			}
		}
	
	
	}
	*/
	
	//return -1 when nothings been touched.
	if (pass->val1 == -1 || pass->val1 == -1) return -1;
	else return 0;
}

//*****************************************TODO

int main(int argc, char **argv){
	//initial parsing
	seed();
	scoredat player1 = { 0 };
	scoredat player2 = { 0 };
	//scoredat test1 = {0}; //you can also init struct using this method, how nice!
	Option option = { 0 };
	int row = 3, col = 3;
	getopt_struct iparam = { 0 }; iparam.optstr = calloc(0xfe, sizeof(char)); //allocate struct in stack first, allocate string contents in the heap after.
	getopt_struct rparam = { 0 }; rparam.optstr = calloc(0xfe, sizeof(char)); //option>>swap
	getopt_struct hparam = { 0 }; hparam.optstr = calloc(0xfe, sizeof(char));
	getopt_struct aparam = { 0 }; aparam.optstr = calloc(0xfe, sizeof(char)); //option>>playa2
	simplegetopt(argc, argv, &iparam, &rparam, &hparam, &aparam);
	if (iparam.on > 0){
		row = atoi(iparam.optstr);
		col = atoi(xtarget(iparam.optstr));
	}
	if (rparam.on > 0) option.swap = 1;
	if (aparam.on > 0) option.playa2 = 1;
	if (col != row) col = row; //needed for square det
	if (hparam.on > 0) help(argc, argv, &iparam, &rparam, &hparam, &aparam);
	free(iparam.optstr);
	free(rparam.optstr);
	free(hparam.optstr);
	free(aparam.optstr);
	if (col < 2){ fprintf(stderr, "determinant is too small!\n"); return 1; }


	//main game
	int totalplaytime, switchuser = 0, i;
	for (totalplaytime = 1;; totalplaytime++){
		if (totalplaytime == 1){ //flip the coin!
#ifndef _WIN32
			printf("\x1b[2J\x1b[0;0H");
#else
			system("cls");
#endif
			printf("lets flip the coin! head is player1, tail is player2"
				"\npress any key to start flipping!...");
			getchar();
			for (i = 0; i < 3; i++){
#ifdef _WIN32
				Sleep(200); //0.2 seconds
#else
				fflush(stdout);
				usleep(200000);
#endif
				printf(". ");
			}
			switch (rand() % 2 + 1){
			case 1: printf("heads.\n"); break;
			case 2: printf("tails.\n"); switchuser++; break;
			}
			printf("press any key to continue...");
			getchar();
		}

		switch (game(row, col, &player1, &player2, totalplaytime, &switchuser, &option)){
		case 1: player1.score++; switchuser++; break;
		case 2: player2.score++; switchuser++; break;
		case 3: break;//tie must be processed on printstatus before this...		
		}
		printstatus(-5, totalplaytime, &player1, &player2, 0);
		printf("next round? Y/N:");
		fflush(stdin);
		char next = getchar();
		switch (next){
		case 'y':;
		case 'Y':;
		case 0xA:break; //linefeed
		default: return 0; //quit game
		}

	}

	return 0;
}

/*TODO:
-still have scoredat->count lying around...maybe i can use it for internal game engine??
-some bullshit happening on freeing array on xcode platform...>:o    -.- will fix later
*/
