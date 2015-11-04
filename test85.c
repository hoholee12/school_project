#include<stdio.h>


typedef struct mystruct {
	int a;
	int b;


} mystruct;

void func(mystruct *hello) {

	hello[0].a = 9000;
	hello[0].b = 69;


}

void func2(mystruct *hello) {
	hello->a = 9000;
	hello->b = 69;


}


int main() {
	mystruct hello[10] = { 0 };
	mystruct hello2 = { 0 };
	func(hello);
	printf("%d %d\n", hello[0].a, hello[0].b);

	func2(&hello2);
	printf("%d %d\n", hello2.a, hello2.b);

	return 0;
}