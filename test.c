#include<stdio.h>

#define swap(a, b){ a^=b;\
					b^=a;\
					a^=b;\
} /*swap macro using XOR*/

/*
#define swap(a, b){ a+=b;\
					b=b-a;\
					a+=b;\
} /*swap macro using add, sub*/
		
int main(){
	int a=0xf, b=0xff;
	printf("a=%d b=%d\n", a, b);
	swap(a, b);
	printf("a=%d b=%d\n", a, b);
	
	
	return 0;
}
