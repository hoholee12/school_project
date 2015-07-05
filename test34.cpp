#include<cstdlib>
#include<cstdio>
#include<signal.h>
#include<cstring>
#include"tools.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wformat="
//common ascii stuff
//0~9 => 48~57
//a~z => 97~122
//A~Z => 65~90

int main(){
	int i=3;
	using array::fibonacci;
	int *x=fibonacci(i); //or array::fibonacci(i); if not using 'using'.
	
	for(int n=0; n<i;n++){
		printf("%d ", x[n]);
	}
	
	return 0;
}