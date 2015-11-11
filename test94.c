#include<stdio.h>

int main() {
	int i = 0;

	/*for (i = 1; i < 10001; i++) printf("%d", i);*/
loop:
	i++;
	printf("%d", i);
	if (i == 10000) goto exit;
	goto loop;

exit:

	printf("im test.\n");
	return 0;
}