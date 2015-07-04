#include<cstdlib>
#include<cstdio>
#include<signal.h>
#include<cstring>
#include"tools.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wparentheses"
//common ascii stuff
//0~9 => 48~57
//a~z => 97~122
//A~Z => 65~90

int main(){
	char a[]="fuck off"; //spawn an array
	char *ptr=&a[0]; //pass the first address to the ptr
	//the above code is basically the same as the under code.
	char *f="motherfucker"; //truncated
	
	printf("%s %s\n", ptr, ptf); //printf's %s needs an ADDRESS of the first character of an array.
	
	return 0;
}