#include<cstdlib>
#include<cstdio>
#include<cstring>
#include"tools.h"


int main(int argc, char **argv){
	//unless malloc or new, everything else is on stack.
	//by that standard, everything here is on stack.
	char a[]="fuck off"; //spawn an array		//right operand is basically a static char arr[9]="fuck off"; pre-defined even before this. also, its NOT constant.
	//a[4]=''; empty character constant is not allowed!!
	a[6]='a';
	a[7]='a';
	char *ptr=&a[0]; //pass the first address to the ptr
	ptr[0]='s';
	ptr[5]='d';
	//the above code is basically the same as the under code.
	char *ptf="motherfucker"; //truncated
	//printf("%d\n", a);
	append(ptf, "SEIG HEIL HITLER ‎REICHSFüHRER-SS", (argv[1])?atoi(argv[1]):4 );
	printf("%s %s\n", ptr, ptf); //printf's %s needs an ADDRESS of the first character of an array.
	return 0;
}