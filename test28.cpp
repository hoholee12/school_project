#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //sleep
#include"test3.h"

#include"test3.h" //guarded.
/*class does not need a wrapper
while enum does...*/
//somethings wrong with enum class.


int main(int argc, char **argv){
	{using gradespace::hello;
	hello hi;
	//exit(0);
	sleep(1);}
	using namespace gradespace::grade_wrapper;
	using stuff::printgrade;
	if(!argv[1]) argv[1]=static_cast<char *>("1337");
	grade test=static_cast<grade>(atoi(argv[1]));
	int result=printgrade(&test);
	if(result) printf("\n\nfail!");
	return(result);
}