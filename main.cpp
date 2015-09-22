#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<unistd.h>
#include<string.h>

// fastest operators: +, -, <<, >>
// 6 times slower than the first one: *
// 240 times(40 times slower than *) slower than the first one: /, %
// DO NOT ALWAYS RELY ON COMPILERS!!

void printbit(int arg=0, int count=8){
	if(count==NULL) count=8; //atoi returns NULL
	int shit=0x1;
	shit<<=count-1;
	for(int i=0; i<count; i++){		//
		if(arg&shit) printf("1");	//this operator will only compare the first bit. its that simple!!
		else printf("0");			//0x80 --> 8 on first 4 bits, 0 on last --> 1000|0000 --> 8 digits.
		arg<<=1;					//shift to the left to compare.
	}
}

//int arr[SIZE]={0}; //do this and it will initialize everything! very convenient aint it?
int main(int argc, char *argv[]){
	printbit(atoi(argv[1]), atoi(argv[2]));
	exit(1);
	
	
	/**************************option parser*************************/
	struct opt_once{
		int opt;
		char *arg;
	};
	opt_once *h=(opt_once *)calloc(1, sizeof(opt_once)); //copy this as many times as you like
	//opt_once *h=(opt_once *)calloc(1, sizeof(opt_once));
	//opt_once *h=(opt_once *)calloc(1, sizeof(opt_once));
	
	
	option long_opts[]={
		{"help", no_argument, 0, 'h'},
		//{"help", no_argument, 0, 'h'},
		//{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	int opt_index; //what?
	for(char c; c!=-1/*EOF*/; c=getopt_long(argc, argv, "h", long_opts, &opt_index)){
		switch(c){
			case 'h': h->opt++; break;
			
		}
		
		
	}
	/****************************************************************/
	
	if(h->opt==1) fprintf(stderr, "Hello, World!\n");
	printf("%d\n", h->opt);
	
	
	
	return 0;
}
