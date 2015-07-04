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
	char *str="fuck off";
	
	for(int i=0;str[i];i++) printf("%s\n", &str[i]);
	//string(&str[i]) as a destination on a loop will loop infinitely.
	//only single char(str[i]) equals int equals boolean
	//therefore we get boolean to determine whether it should be terminated or not.
	
	//more direct way
	//str is an address to the first character of an array.
	//therefore *str will represent the first character itself.
	for(;*str;str++) printf("%s\n", str);
	//&str[0]++ is not a valid syntax, so str++.
	
	return 0;
}