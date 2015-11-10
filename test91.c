#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFFER 1024


typedef struct _strcount {
	int score;
	char *loc;


} _strcount;

void strcount(char *input, _strcount *strcount, int buffer) {
	int i, j, k, l;
	_strcount *temp=NULL;
	int temp2;
	char **arr = calloc(buffer, sizeof*arr);
	/*sanitize*/
	for (i = 0; input[i + 1]; i++);
	if (input[i] == '\n')input[i] = 0;

	/*separate*/
	j = 0; /*count arr*/
	arr[0] = input;
	for (i = 0; input[i]; i++) {
		if (!isalpha(input[i])) {
			input[i] = 0;
			if (isalpha(input[i + 1])) arr[++j] = &input[i + 1];
		}
		else if (isupper(input[i])) input[i] = tolower(input[i]);
	}

	/*store*/
	k = 0; /*if i am first*/
	for (i = 0; arr[i]; i++) {
		l = 0; /*condition check*/
		for (j = 0; strcount[j].loc; j++) {
			if (!strcmp(strcount[j].loc, arr[i])) { /*if i am not the first*/
				strcount[j].score++;
				l++;
				break;
			}
		}
		if (!l) { /*if i am first*/
			strcount[k].score++;
			strcount[k++].loc = arr[i];
		}
	}

	/*sort by alphabetical order*/
	for (j = 0; strcount[j + 1].loc; j++) {
		for (i = 0; strcount[i + 1].loc; i++) {
			if (strcmp(strcount[i].loc, strcount[i + 1].loc) > 0) {
				/*align loc*/
				temp = strcount[i + 1].loc;
				strcount[i + 1].loc = strcount[i].loc;
				strcount[i].loc = temp;
				/*align score*/
				temp2 = strcount[i + 1].score;
				strcount[i + 1].score = strcount[i].score;
				strcount[i].score = temp2;
			}


		}
	}
}

int main() {
	int i, j, k, l;
	
	char input[BUFFER] = { 0 };
	_strcount test[BUFFER] = { 0 };
	printf("문자열을 입력하시오: ");
	fgets(input, BUFFER, stdin);

	strcount(input, test, BUFFER);
	/*print*/
	printf(	"===============\n"
			"단어\t빈도\n"
			"===============\n");
	for (i = 0; test[i].loc; i++) {
		printf("%s:\t%d\n", test[i].loc, test[i].score);
	
	
	}






	return 0;
}