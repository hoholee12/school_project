/*created by hoholee12*/

#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _strcount {
	int score;
	char *loc;


} _strcount;

void strcount(char *input, _strcount *_strcount, int buffer) {
	int i, j, k, l;
	char **arr = calloc(buffer, sizeof*arr);
	/*sanitize*/
	for (i = 0; input[i + 1]; i++);
	if (input[i] == '\n')input[i] = 0;

	/*separate*/
	j = 0;
	arr[0] = input;
	for (i = 0; input[i]; i++) {
		if (!isalpha(input[i])) {
			input[i] = 0;
			if (isalpha(input[i + 1])) arr[++j] = &input[i + 1];
		}
		else if (isupper(input[i])) input[i] = tolower(input[i]);
	}

	/*store*/
	k = 0;
	for (i = 0; arr[i]; i++) {
		l = 0; /*condition check*/
		for (j = 0; _strcount[j].loc; j++) {
			if (!strcmp(_strcount[j].loc, arr[i])) { /*if i am not the first*/
				_strcount[j].score++;
				l++;
				break;
			}
		}
		if (!l) { /*if i am first*/
			_strcount[k].score++;
			_strcount[k++].loc = arr[i];
		}
	}

}

void mystrstr(char *input, char *replacefrom, char *replacewith, char *result) {
	int i, j, k, l;


	/*sanitize*/
	for (i = 0; input[i+1]; i++);
	if(input[i]=='\n') input[i] = 0;
	for (i = 0; replacefrom[i+1]; i++);
	if (replacefrom[i] == '\n') replacefrom[i] = 0;
	for (i = 0; replacewith[i+1]; i++);
	if (replacewith[i] == '\n') replacewith[i] = 0;
	
	/*find match*/
	for (i = 0; input[i]; i++) {
		for (k = 0; replacefrom[k]; k++); /*strlen*/
		for (j = 0; j<k; j++) {
			if (input[i + j] != replacefrom[j]) {
				break;
			}

		}
		if (k == j) {
			break;


		} /*match!*/


	}
	k = 0;
	
	/*start writing*/
	for (l = 0; input[l]; l++) {
		if (i == l) {
			for (k = 0; replacewith[k]; k++) {
				result[l + k] = replacewith[k];
			}
			k--; /*hax*/
			for (j = 0; replacefrom[j]; j++); /*strlen*/
			j--; /*hax*/
		}
		else {
			if(k) result[l + k] = input[l + j]; /*if replace occured*/
			else result[l] = input[l];
		}
	}
	result[l + k] = 0; /*end with null*/
	
}