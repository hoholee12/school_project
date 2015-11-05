#include<stdio.h>
#define buffer 1024

int main() {
	char arr[buffer] = "34.9000 3.64000";
	double a, b;
	sscanf(arr, "%lg %lg", &a, &b);
	fprintf(stdout, "%g %g\n", a, b);

	snprintf(arr, buffer, "%g %g", a, b);
	fprintf(stdout, "%s\n", arr);

	return 0;
}