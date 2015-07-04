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
	//unless malloc or new, everything else is on stack.

	char a[]="fuck off"; //spawn an array								//this is on stack
	char *ptr=&a[0]; //pass the first address to the ptr 				//stack
	//the above code is basically the same as the under code.
	char *f="motherfucker"; //truncated 								//this is also on stack
	
	printf("%s %s\n", ptr, ptf); //printf's %s needs an ADDRESS of the first character of an array.
	
	return 0;
}