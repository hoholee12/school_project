#include<stdio.h>
#include<stdlib.h>

int main(){
	system("export LINES=$(stty size | awk '{print $1}')"
		"export COLUMNS=$(stty size | awk '{print $2}')");
	printf("%s %s\n", getenv("LINES"), getenv("COLUMNS"));

	//Heisenbug?
	//undefined behaviour, system() sets these exports on itself. system() itself is child process.
	//therefore NULL will return in getenv and cause all this shitty grief!!
	//use setenv()..
	return 0;
}
