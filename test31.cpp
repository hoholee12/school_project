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
	{
		char c[1024]; //there are some functions that will not work if the string format is uninitialized.
		gets(c);
		puts(c);
	}{ //gets and getchar stdin method is radically different.
		char c;
		c=getchar();
		putchar(c);
	}
	return 0;
}