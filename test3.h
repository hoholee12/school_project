#pragma once

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
