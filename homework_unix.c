/*homework.c - a tic-tac-toe game!
* Copyright (C) 2015  hoholee12@naver.com
*
* May be freely distributed and modified as long as copyright
* is retained.
*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

/*#define DEBUG*/
/*#define SPEEDY_GONZALES
*/
typedef struct scoredat{
	int score;
	int count;
}scoredat;

typedef struct _level{
	int on;
	int level;

} _level;
typedef struct _option{
	int swap;
	_level playa1;
	_level playa2;
} _option;

typedef struct input_alt{
	int val1;
	int val2;
} input_alt;

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

#define printf(str, args...); \
		fflush(stdout);		/*for dots*/\
		printf(str, ##args);\
		fflush(stdout);

void printarr_alt(int **arr, int row, int col,
	int user,
	int err,
	const char *str,
	_option *option
	){
	int player1_count = 0, player2_count = 0, i, j;
	printf("\x1b[2J\x1b[0;0H");
	printf("\t");
	for (i = 1; i <= row; i++){ printf("%d\t", i);}



	printf("Options: ");
	if (option->swap == 1) printf("SWP ");
	if (option->playa2.on == 1) printf("AUTO ");
	if (option->playa2.level) printf("LVL%d ", option->playa2.level);

	if (option->playa1.on == 1) printf("P1CPU ");
	if (option->playa1.level) printf("LVL%d ", option->playa1.level);

	printf("\n");

	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			switch (arr[i][j]){
			case 0: break;
			case 1: player1_count++; break;
			case 2: player2_count++; break;
			}
		}
	}

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
			printf("player1=%d/%d  player2=%d/%d  total=%d/%d",
				player1_count, row*row / 2, player2_count, row*row / 2, player1_count + player2_count, row*row);
		}
		if (i == 1){
			if (option->playa2.on == 1 && user == 2){
				switch (err){
				case -4: printf("\t%s", str); break;
				default: printf("\tplayer%d's turn!", user); break;
				}

			}
			else if (option->playa1.on == 1 && user == 1){
				switch (err){
				case -4: printf("\t%s", str); break;
				default: printf("\tplayer%d's turn!", user); break;
				}

			}
			else{
				switch (err){
				case -1: printf("\tyou can't go there!"); break;
				case -2: printf("\tHOW DID YOU GET HERE?! xDDD"); break;
				case -3: printf("\twhat?"); break;
				case -4: printf("\t%s", str); break;
				default: printf("\tplayer%d's turn!", user); break;
				}
			}
		}
		printf("\n\n");

	}


}



int dividenum(int row){
	int count = 0, i;
	for (i = 1; row / i; i *= 10) count++;
	return count;
}

int advinput_alt(
	input_alt *pass,
	int row, int col
	){
	int i, buffer=0xff/*255*/;
	char *input=NULL;
	fflush(stdin);
	input = (char *)calloc(dividenum(row) * 2 + 2, sizeof(char));
	input = (char *)realloc(input, buffer);
	fgets(input, buffer, stdin);
	if (input[0] == 'q'){
		pass->val1 = 'q';
		return 0;
	}
	pass->val1 = atoi(input) - 1;
	pass->val2 = -1;

	for (i = 0; input[i]; i++){
		if (input[i] == 'x'){
			pass->val2 = atoi(&input[i + 1]) - 1;
			break;
		}

	}
	if (pass->val2 == -1) pass->val1 = -3;
	free(input);
	return 0;
}

int game_engine(
	int **arr, int row, int col,
	input_alt *pass,
	_option *option,
	int user
	);



int userinput_alt(int **arr, int row, int col,
	int user,
	_option *option
	){
	int i, result_r = row, result_c = col, max = row - 1, min = 0;
	input_alt pass = { 0 };
	if (option->playa2.on == 1 && user == 2){
		printf("player2 is thinking");
#ifndef SPEEDY_GONZALES
		for (i = 0; i < 3; i++){
			
			printf(".");
			usleep(200*1000);
		}
#endif
		if (game_engine(arr, row, col, &pass, option, user) == -1){
			fprintf(stderr, "game_engine() crashed!!");
			exit(1);
		}
	}
	else if (option->playa1.on == 1 && user == 1){
		printf("player1 is thinking");
#ifndef SPEEDY_GONZALES
		for (i = 0; i < 3; i++){
			
			printf(".");
			usleep(200*1000);
		}
#endif
		if (game_engine(arr, row, col, &pass, option, user) == -1){
			fprintf(stderr, "game_engine() crashed!!");
			exit(1);
		}
	}
	else{
		printf("player%d>>", user);
		advinput_alt(&pass, row, col);
	}
	switch (pass.val1){
	case 'q': return -2;
	case -3: return -3;
	}

	if (pass.val1>max || pass.val1<min) return -1;
	if (pass.val2>max || pass.val2<min) return -1;

	if (option->swap == 1 && user != 2){
		if (arr[pass.val2][pass.val1] != 0) return -1;
		arr[pass.val2][pass.val1] = user;
	}
	else{
		if (arr[pass.val1][pass.val2] != 0) return -1;
		arr[pass.val1][pass.val2] = user;
	}
	return 0;
}



int **allocarr(int **arr, int row, int col){
	int i;
	arr = (int **)calloc(row, sizeof(int));
	malloc(row*sizeof(int)); /*hack*/
	for (i = 0; i<row; i++){
		arr[i] = (int *)calloc(col, sizeof(int));
	}
	return arr;
}

void freearr(int **arr, int row, int col){
	int i;
	for (i = 0; i < row; i++) free(arr[i]);
	free(arr);

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
	int i, j, bak, bad, p1_exists, p2_exists, notatie;
	/*row*/
	for (i = 0; i < row; i++){
		bak = arr[i][0];
		bad = 0;
		for (j = 1; j < col; j++){
			if (arr[i][j] != bak){
				bad = 1;
				break;

			}
		}
		if ((!bad) && (bak != 0)) return bak;
	}
	/*col*/
	for (i = 0; i < row; i++){
		bak = arr[0][i];
		bad = 0;
		for (j = 1; j < col; j++){
			if (arr[j][i] != bak){
				bad = 1;
				break;

			}
		}
		if ((!bad) && (bak != 0)) return bak;
	}
	/*diagonal*/
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

	
	notatie = 0;
	for (i = 0; i<row; i++){
		p1_exists = 0;
		p2_exists = 0;
		for (j = 0; j<col; j++){
			if (arr[i][j] == 1) p1_exists++;
			else if (arr[i][j] == 2) p2_exists++;



		}
		if ((p1_exists&&!p2_exists) || (!p1_exists&&p2_exists) || (!p1_exists&&!p2_exists)){
			notatie++; 
			break;
		}
	}
	for (i = 0; i<row; i++){
		p1_exists = 0;
		p2_exists = 0;
		for (j = 0; j<col; j++){
			if (arr[j][i] == 1) p1_exists++;
			else if (arr[j][i] == 2) p2_exists++;



		}
		if ((p1_exists&&!p2_exists) || (!p1_exists&&p2_exists) || (!p1_exists&&!p2_exists)){
			notatie++; 
			break;
		}
	}
	p1_exists = 0;
	p2_exists = 0;
	for (i = 0; i<row; i++){
		if (arr[i][i] == 1) p1_exists++;
		else if (arr[i][i] == 2) p2_exists++;


	}
	if ((p1_exists&&!p2_exists) || (!p1_exists&&p2_exists) || (!p1_exists&&!p2_exists)) notatie++; 

	p1_exists = 0;
	p2_exists = 0;
	for (i = 0; i<row; i++){
		if (arr[i][row - i - 1] == 1) p1_exists++;
		else if (arr[i][row - i - 1] == 2) p2_exists++;


	}
	if ((p1_exists&&!p2_exists) || (!p1_exists&&p2_exists) || (!p1_exists&&!p2_exists)) notatie++; 


	if (!notatie) return 3; 

	return 0;
}


/*
return 0 => normal
return 1 => normal(won or lost)
return -1 => abnormal(undecided, crashed)
*/
#define ENGINE_REVERSE 
/*#define ENGINE_OFFVSDEF
*/
/*
list of engine speed/performance rank(AUTO LVL1 P1CPU LVL1):
1st (about 29~46/100) => ENGINE_REVERSE on, ENGINE_OFFVSDEF off
2nd (about 38~45/100) => ENGINE_REVERSE off, ENGINE_OFFVSDEF on
3rd (about 40~54/100) => ENGINE_REVERSE on, ENGINE_OFFVSDEF on
4th (about 68~96/100) => ENGINE_REVERSE off, ENGINE_OFFVSDEF off

more than LVL1 will give much more varied results that defeats the purpose of ranking.
*/


_level *player1_option(int row, _option *option){

	
	if (option->playa1.level < 1) option->playa1.level = 1;
	else if (option->playa1.level>row - 1) option->playa1.level = row - 1;
	return &option->playa1;
}

_level *player2_option(int row, _option *option){

	
	if (option->playa2.level < 1) option->playa2.level = 1;
	else if (option->playa2.level>row - 1) option->playa2.level = row - 1;
	return &option->playa2;
}

int game_engine(
	int **arr, int row, int col,	
	input_alt *pass,				
	_option *option,
	int user
	){
	_level *engine_option=NULL;

	int i, j, k, broken = 0, nostart = 0, startloc_x = 0, startloc_y = 0, worse, minor_y = -1, minor_x = -1, prev_brain;
	
	int **brain = NULL;
	
	pass->val1 = -1;
	pass->val2 = -1;

	if (user == 1) engine_option = player1_option(row, option);
	else if (user == 2) engine_option = player2_option(row, option);


#ifdef ENGINE_REVERSE
	prev_brain = -3;/*minimum*/
#else
	prev_brain = 3;/*maximum*/
#endif

	
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
	
	if (nostart == 1){
		for (;;){
			pass->val1 = startloc_y + (rand() % 3 - 1);
			pass->val2 = startloc_x + (rand() % 3 - 1);
			if ((pass->val1 >= 0 && pass->val1 <= row) && (pass->val2 >= 0 && pass->val2 <= row) && ((pass->val1 != startloc_y) || (pass->val2 != startloc_x))) break;
		}
		return 0;
	}


	
	/*
	3==row col diag combined
	2==two of these combined
	1==just one
	something like that...

	we want to place our piece in the smallest number possible(-3 is the smallest) to win faster!
	*/


	
	brain = allocarr(brain, row, col);
	
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[i][j] == 1){
				for (k = 0; k < col; k++) brain[i][k]++; 
				break;
			}
			if (arr[i][j] == 2){
				for (k = 0; k < col; k++) brain[i][k]--; 
				break;
			}
		}

	}
	
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[j][i] == 1){
				for (k = 0; k < col; k++) brain[k][i]++; 
				break;
			}
			if (arr[j][i] == 2){
				for (k = 0; k < col; k++) brain[k][i]--; 
				break;
			}
		}

	}
	
	for (i = 0; i < row; i++){
		if (arr[i][i] == 1){
			for (k = 0; k < col; k++) brain[k][k]++; 
			break;

		}
		if (arr[i][i] == 2){
			for (k = 0; k < col; k++) brain[k][k]--; 
			break;

		}
	}
	
	for (i = 0; i < row; i++){
		if (arr[i][row - i - 1] == 1){
			for (k = 0; k < col; k++) brain[k][row - k - 1]++; 
			break;

		}
		if (arr[i][row - i - 1] == 2){
			for (k = 0; k < col; k++) brain[k][row - k - 1]--; 
			break;

		}
	}

#ifdef DEBUG
	for (i = 0; i < row; i++){
		printf("\n\n");
		for (j = 0; j < col; j++){
			printf("\t%d", brain[i][j]);
		}
	}
	getchar();

#endif

	
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
#ifdef ENGINE_REVERSE
			if (brain[i][j]>prev_brain&&arr[i][j] == 0){
#else
			if (brain[i][j]<prev_brain&&arr[i][j] == 0){
#endif
				prev_brain = brain[i][j];
				pass->val1 = i;
				pass->val2 = j;
			}

			}

		}

	
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
			if (arr[i][j] == 2) worse++;
			else if (arr[i][j] == 1){
				broken = 1;
				break;
			}
			else minor_x = j;
		}
		if (broken == 1);
		else if (worse >= engine_option->level){
			pass->val1 = i;
			pass->val2 = minor_x;
		}
	}
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
			if (arr[j][i] == 2) worse++;
			else if (arr[j][i] == 1){
				broken = 1;
				break;
			}
			else minor_y = j;
		}
		if (broken == 1);
		else if (worse >= engine_option->level){
			pass->val1 = minor_y;
			pass->val2 = i;
		}
	}
	
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
	else if (worse >= engine_option->level){
		pass->val1 = minor_x;
		pass->val2 = minor_x;
	}
	
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
	else if (worse >= engine_option->level){
		pass->val1 = minor_y;
		pass->val2 = minor_x;
	}

	
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
			if (arr[i][j] == 1) worse++;
			else if (arr[i][j] == 2){
				broken = 1;
				break;
			}
			else minor_x = j;
		}
		if (broken == 1);
#ifdef ENGINE_OFFVSDEF
		else if (worse >= engine_option->level){
#else
		else if (worse >= row - 1){
#endif
			pass->val1 = i;
			pass->val2 = minor_x;
		}
		}
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
			if (arr[j][i] == 1) worse++;
			else if (arr[j][i] == 2){
				broken = 1;
				break;
			}
			else minor_y = j;
		}
		if (broken == 1);
#ifdef ENGINE_OFFVSDEF
		else if (worse >= engine_option->level){
#else
		else if (worse >= row - 1){
#endif
			pass->val1 = minor_y;
			pass->val2 = i;
		}
		}
	
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
#ifdef ENGINE_OFFVSDEF
	else if (worse >= engine_option->level){
#else
	else if (worse >= row - 1){
#endif
		pass->val1 = minor_x;
		pass->val2 = minor_x;
	}
	
	worse = 0;
	broken = 0;
	for (i = 0; i < row; i++){
		if (arr[i][row - i - 1] == 1) worse++;
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
#ifdef ENGINE_OFFVSDEF
	else if (worse >= engine_option->level){
#else
	else if (worse >= row - 1){
#endif
		pass->val1 = minor_y;
		pass->val2 = minor_x;
	}

	
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
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
		}
	}
	
	for (i = 0; i < row; i++){
		worse = 0;
		broken = 0;
		for (j = 0; j < col; j++){ 
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
		}
	}
	
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
	}
	
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
	}




	
	if (pass->val1 == -1 || pass->val2 == -1){
		pass->val1 = rand() % row;
		pass->val2 = rand() % row;
	}

	freearr(brain, row, col); 
	
	if (pass->val1 == -1 || pass->val2 == -1) return -1;
	else return 0;
	}

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

			 if (player1->score > player2->score){printf("\nplayer1 won by +%d points", player1->score - player2->score);}
			 else if (player1->score == player2->score){printf("\nits a tie.");}
			 else{printf("\nplayer2 won by +%d points", player2->score - player1->score);}

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
	_option *option
	){
	int **arr = NULL, user, inputstate;
	
	
	arr = allocarr(arr, row, col);
	user = *switchuser % 2 + 1; 

	for (;;){ 


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
			
		}
		(*switchuser)++; 
		user = *switchuser % 2 + 1;
	}
	return 0;

}

/*game return info
-return 1: player1 wins
-return 2: player2 wins
-return 3: its a tie*/

void seed(){
	srand((unsigned)time(NULL));

}


typedef struct getopt_struct{
	int on;
	char *optstr; 
} getopt_struct;

void simplegetopt(
	int argc, char **argv,
	getopt_struct *iparam,
	getopt_struct *rparam,
	getopt_struct *hparam,
	getopt_struct *aparam,
	getopt_struct *vparam
	){
	int i;
	for (i = 1; i<argc; i++){
		if (!strcmp(argv[i], "-i")){ 
			if (strlen(argv[i + 1])>0xFD){ fprintf(stderr, "buffer overflow!\n"); abort(); } 
			iparam->on++;
			if (i + 1 < argc) strcpy(iparam->optstr, argv[++i]); 
			else strcpy(iparam->optstr, "3x3"); 
		}
		else if (!strcmp(argv[i], "-r")){
			rparam->on++;
		}
		else if (!strcmp(argv[i], "-h")){
			hparam->on++;
		}
		else if (!strcmp(argv[i], "-a")){
			aparam->on++;
			if (i + 1 < argc) strcpy(aparam->optstr, argv[++i]); 
			else strcpy(aparam->optstr, "1"); 
		}
		else if (!strcmp(argv[i], "-v")){
			vparam->on++;
			if (i + 1 < argc) strcpy(vparam->optstr, argv[++i]); 
			else strcpy(vparam->optstr, "1"); 
		}
	}

}

void help(int argc, char **argv,
	getopt_struct *iparam,
	getopt_struct *rparam,
	getopt_struct *hparam,
	getopt_struct *aparam,
	getopt_struct *vparam
	){
	fprintf(stderr, "homework.c - a tic-tac-toe game!"
		"\nCopyright(C) 2015  hoholee12@naver.com"
		"\nUsage: %s -i [row]x[col] -r -a [level: 1(most aggressive) ~ row-1(least aggressive)] -v [level: 1(most aggressive) ~ row-1(least aggressive)]"
		"\n\t-i sets derterminant size by [row]x[col]"
		"\n\t-r reverses [row][col] input ingame"
		"\n\t-a is a computer opponent"
		"\n\t-v player1 is a computer\n\n", argv[0]);
	free(iparam->optstr);
	free(rparam->optstr);
	free(hparam->optstr);
	free(aparam->optstr);
	free(vparam->optstr);
	exit(0);
};


char *xtarget(char *arg){ 
	int i;
	for (i = 0; arg[i]; i++){
		if (arg[i] == 'x') return &arg[i + 1];
	}
	return NULL;
}

int main(int argc, char **argv){
	scoredat player1 = { 0 };
	scoredat player2 = { 0 };
	_option option = { 0 };
	int row = 3, col = 3;
	int totalplaytime, switchuser = 0, i;
	char next;
	
	getopt_struct iparam = { 0 }; 
	getopt_struct rparam = { 0 }; 
	getopt_struct hparam = { 0 }; 
	getopt_struct aparam = { 0 }; 
	getopt_struct vparam = { 0 }; 
	iparam.optstr = (char *)calloc(0xfe, sizeof(char));
	rparam.optstr = (char *)calloc(0xfe, sizeof(char));
	hparam.optstr = (char *)calloc(0xfe, sizeof(char));	
	aparam.optstr = (char *)calloc(0xfe, sizeof(char)); 
	vparam.optstr = (char *)calloc(0xfe, sizeof(char));
	
	seed();	
	simplegetopt(argc, argv, &iparam, &rparam, &hparam, &aparam, &vparam);
	if (iparam.on > 0){
		row = atoi(iparam.optstr);
		col = atoi(xtarget(iparam.optstr));
	}
	if (rparam.on > 0) option.swap = 1;
	if (aparam.on > 0){
		option.playa2.on = 1;
		option.playa2.level = atoi(aparam.optstr);
		if (!option.playa2.level) option.playa2.level = 1; 
	}
	if (vparam.on > 0){
		option.playa1.on = 1;
		option.playa1.level = atoi(vparam.optstr);
		if (!option.playa1.level) option.playa1.level = 1; 
	}
	if (col != row) col = row; 
	if (hparam.on > 0) help(argc, argv, &iparam, &rparam, &hparam, &aparam, &vparam);
	free(iparam.optstr);
	free(rparam.optstr);
	free(hparam.optstr);
	free(aparam.optstr);
	free(vparam.optstr);
	if (col < 2){ fprintf(stderr, "determinant is too small!\n"); return 1; }


	
	for (totalplaytime = 1;; totalplaytime++){
		if (totalplaytime == 1){ 
			printf("\x1b[2J\x1b[0;0H");
			printf("lets flip the coin! head is player1, tail is player2"
				"\npress any key to start flipping!...");
			getchar();
			for (i = 0; i < 3; i++){
				
				printf(".");
				usleep(200*1000);
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
		case 3: break;
		}
		printstatus(-5, totalplaytime, &player1, &player2, 0);
		printf("next round? Y/N:");
		fflush(stdin);
		next = getchar();
		switch (next){
		case 'y':;
		case 'Y':;
		case 0xA:break; 
		default: return 0; 
		}

	}

	return 0;
}
