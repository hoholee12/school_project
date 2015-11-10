#include<stdio.h>
#include<string.h>

int main(){
	char munja[80] = { 0 };
	char smunja[80] = { 0 };
	char cmunja[80] = { 0 };
	char result[80] = { 0 };
	char *loc = NULL;
	int i, j;
	printf("문자열을 입력하세요: ");
	gets(munja);
	printf("찾을 문자열: ");
	gets(smunja);
	printf("바꿀 문자열: ");
	gets(cmunja);

	loc = strstr(munja, smunja);
	j = 0;
	if (loc) {
		for (i = 0; i < strlen(munja); i++) {
			if (loc == &munja[i]) {
				for (j = 0; j < strlen(cmunja); j++) {
					result[i + j] = cmunja[j];
				
				}
			
			}
			if (j > 0) {
				result[i + j] = munja[i+strlen(smunja)];
			}
			else {
				result[i] = munja[i];
			
			}
		}


		printf("결과: %s\n", result);
	
	}
	else printf("문자열을 찾을 수 없습니다.\n");


	return 0;
}