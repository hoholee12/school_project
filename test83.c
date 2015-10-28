#include<stdio.h>

int main() {
	int x = 0x12345678;
	char *xp = (char *)&x; /*biggest> 12 | 34 | 56 | 78 >smallest*/
	printf("바이트 순서: %x %x %x %x\n", xp[0], xp[1], xp[2], xp[3]); /*78 | 56 | 34 | 12 <== little-endian*/

	short *_xp = (short *)&x; /*biggest> 1234 | 5678 >smallest*/
	printf("2바이트 순서: %x %x\n", _xp[0], _xp[1]); /*5678 | 1234 <== little-endian*/


	return 0;
}