#include<stdio.h>
#define buffer 1024

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
	
}


int main() {
	char input[buffer] = {0};
	char replacefrom[buffer] = { 0 };
	char replacewith[buffer] = { 0 };
	char result[buffer] = {0};
	
	
	
	printf("문자열을 입력하시오: ");
	fgets(input, buffer, stdin);
	printf("찾을 문자열: ");
	fgets(replacefrom, buffer, stdin);
	printf("바꿀 문자열: ");
	fgets(replacewith, buffer, stdin);


	mystrstr(input, replacefrom, replacewith, result);

	printf("결과: %s\n", result);

	return 0;
}