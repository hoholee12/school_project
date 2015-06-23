#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //sleep
#include"test3.h"

#include"test3.h" //guarded.
/*class does not need a wrapper
while enum does...*/
//somethings wrong with enum class.

//namespace=enum=class=struct=union all similar syntax
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
	};
	class hello{
	public:
		hello(){printf("hello!\n");}
	
	};
};
namespace stuff{
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
};

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