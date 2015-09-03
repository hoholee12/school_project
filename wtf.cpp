#include<stdio.h>
#include<stdlib.h>

int main(){
	system("export LINES=$(stty size | awk '{print $1}')"
		"export COLUMNS=$(stty size | awk '{print $2}')");
	printf("%s %s\n", getenv("LINES"), getenv("COLUMNS"));

	//Heisenbug?
	return 0;
}
