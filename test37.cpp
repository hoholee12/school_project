#include<cstdlib>
#include<cstdio>
#include<cstring>
#include"tools.h"

union position{
	char classy;
	char department[5]="test"; 

};

int main(){
	position fuck;
	mystrcpy(fuck.department, "a");
	printf("%s\n", fuck.department);
	printf("%d\n", sizeof(fuck.department));
	
	double x=1.2;
	//printf("%d\n", mypow(3,3));
	mypow(x, 3, 1);
	printf("%f\n", x);
	return 0;
}

//0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

//0xDEADBEEF
//Dx16^7+Ex16^6+Ax16^5+Dx16^4+Bx16^3+Ex16^2+Ex16^1+Fx16^0
//F		E		E		B		D		A			E			D
//15	14		14		11		13		10			14			13
//1		16		256		4096	65536	1048576		16777216	268435456

//15	224		3584	45056	851968	10485760	234881024	3489660928

//373598559