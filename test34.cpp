#include<cstdlib>
#include<cstdio>
#include<signal.h>
#include<cstring>
#include"tools.h"

int main(int argc, char **argv){
	s32 i=10;
	if(argv[1]) i=atoi(argv[1]);
	using array::fibonacci;
	s32 *x=fibonacci(i); //or array::fibonacci(i); if not using 'using'.
	
	for(s32 n=0; n<i;n++){
		printf("%d ", x[n]);
	}
	
	return 0;
}