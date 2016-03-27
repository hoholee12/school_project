#include<stdio.h>
#include<time.h>

void move(int *a, int *b) {
	(*a)--; (*b)++;
}

void hanoi_tower(int n, int* A, int* B, int* C) {
	if (n == 1) move(A, C);
	else {
		hanoi_tower(n - 1, B, A, C);
		move(A, C);
		hanoi_tower(n - 1, A, C, B);
	}
}

int hanoi_count(int n, int* A, int* B, int* C) {
	if (n == 1) return 1;
	else {
		return hanoi_count(n - 1, B, A, C) + 1 + hanoi_count(n - 1, A, C, B);;
	}
}

int main() {
	clock_t start, end;
	int A = 0, B = 0, C = 0;
	int n, count = 0;
	int i;
	scanf("%d", &n);
	for (i = 3;i<=n;i++) {
		start = clock();
		count = hanoi_count(i, &A, &B, &C);
		end = clock();
		printf("%d plates count = %d taken time = %gsecs\n", i, count, (double)(end - start)/CLOCKS_PER_SEC);
	}
	return 0;

}