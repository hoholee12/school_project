#include<stdio.h>
#include<stdarg.h>
#define va_copy(dest, src) ((dest) = (src))

typedef struct _test {
	int hello;



} _test;

void test2() {
	printf("i am test\n");


}

void test(int count, ...) {
	va_list argp1, argp2;
	_test *temp = NULL;
	int morecount = count;
	va_start(argp1, count);
	va_copy(argp2, argp1);
	for (; count > 0; count--) {
		temp = va_arg(argp1, _test *);
		printf("%d\n", temp->hello);
	}
	va_end(argp1);
	printf("next:\n");
	for (; morecount > 0; morecount--) {
		temp = va_arg(argp2, _test *);
		printf("%d\n", temp->hello);
	
	}
	va_end(argp2);
}

int main() {
	_test t[5] = { {0} };
	t[1].hello = 420;
	t[3].hello = 69;
	test(5, &t[0], &t[1], &t[2], &t[3], &t[4]);


	return 0;
}