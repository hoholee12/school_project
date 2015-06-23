#include<stdio.h>
#include<stdlib.h>

namespace gradespace{
	namespace grade_wrapper{
		enum grade{
			a,
			b,
			c,
			d,
			e,
			f
		};
	}
	
}

using namespace gradespace::grade_wrapper;
int printgrade(grade *test){
	switch(*test /*just 'test' is an address to *test.*/){
		case a:
			printf("a");
			break;
		case b:
			printf("b");
			break;
		case c:
			printf("c");
			break;
		case d:
			printf("d");
			break;
		case e:
			printf("e");
			break;
		case f:
			printf("f");
			break;
		default:
			printf("what?");
			return(1);
	}
	return(0);
}

int main(int argc, char **argv){
	if(!argv[1]) argv[1]=static_cast<char *>("1337");
	grade test=static_cast<grade>(atoi(argv[1]));
	int result=printgrade(&test);
	if(result) printf("\n\nfail!");
	return(result);
}