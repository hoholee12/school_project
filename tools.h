/*
*	tools.h
*	collection of tools for convenience
*	Copyright (c) 2015 hoholee12@naver.com
*/

//	stuff<<=1; => stuff*=2;
//	stuff<<=2; => stuff*=2*2;
//	stuff<<=2; => stuff*=2*2*2;
/*
*	i*2 = i<<1
*	i*3 = (i<<1) + i
*	i*10 = (i<<3) + (i<<1)
*/
//printbit - char ch -128~127 unsigned 0~255
void printbit(unsigned int ch/*prevent overflow*/, int count=8){
	int arr[count];
	for(int i=(count-1);i>=0;i--){
		arr[i]=ch%2;
		ch/=2;
	}
	for(int i=0; i<count; i++){
		printf("%d", arr[i]);
	}
}


//append - call string_tools first to init. written as a class because it needs a destructor.
#include<cstdio>
#include<cstdlib>
class string_tools{
private:
	char *c=new char[INT_MAX]; //dyna alloc // outside b/c destructor needs it.
public:
	string_tools(){}
	bool append(char *&a/*THIS IS HOW YOU REFERENCE A POINTER!!!*/, int x, char *b){
		if(!c){ fprintf(stderr,"alloc failed!"); //fail
			return EXIT_FAILURE;
		}
		int y=0;
		for(int i=0; a[i]; i++){
			if(x==i){
				for(int j=0; b[j]; j++){
					c[y++]=b[j];
				}
			}
			else c[y++]=a[i];
		}
		a=c;
		//printf("%d	%d\n", a, c);
		return EXIT_SUCCESS;
	}	
	~string_tools(){delete [] c;}
};

