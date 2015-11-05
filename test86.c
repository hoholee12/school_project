#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define buffer 1024
#define tostr2(x) #x
#define tostr(x) tostr2(x)

int main() {
	char str[buffer] = {0};
	double a, b, result;
	printf("연산을 입력하시오: ");
	fscanf(stdin, "%"tostr(buffer)"s %lf %lf", str, &a, &b);
	if (!strcmp(str, "add")) result = a + b;
	else if (!strcmp(str, "sub")) result = a - b;
	else if (!strcmp(str, "mul")) result = a * b;
	else if (!strcmp(str, "div")) result = a / b;
	else exit(1);
	printf("연산의 결과: %g\n", result);

	return 0;
}