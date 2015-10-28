#include<stdio.h>

/*least common multiple = lcm 최소 공배수
great common divisor = gcd 최대 공약수*/

#define swap(x, y) do{\
	x = x + y;\
	y = x - y;\
	x = x - y;\
 } while (0);

void get_lcm_gcd(int x, int y, int *p_lcm, int *p_gcd) {
	int r, xb=x, yb=y;
	if (x < y) swap(x, y);
	for (;;) {
		if (y == 0) { /*if smaller one equals zero*/
			*p_gcd = x;
			break;
		}
		else {
			r = x%y; /*remainder*/
			x = y; /*smaller one to bigger one*/
			y = r; /*remainder to smaller one*/
		}
	}
	*p_lcm = (xb*yb) / *p_gcd;
}


int main() {
	int x, y;
	int lcm, gcd;


	printf("x=");
	scanf("%d", &x);
	printf("y=");
	scanf("%d", &y);


	get_lcm_gcd(x, y, &lcm, &gcd);

	printf("x=%d y=%d: lcm=%d gcd=%d\n", x, y, lcm, gcd);


	return 0;
}