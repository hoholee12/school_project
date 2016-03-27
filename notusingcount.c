#include<stdio.h>
#include<time.h>


int fibo_rec(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibo_rec(n - 1) + fibo_rec(n - 2);
}

int cnt_fibo_rec(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 0;
	else return cnt_fibo_rec(n - 1) + cnt_fibo_rec(n - 2) + 3;
}



int fibo_iter(int n) {
	if (n < 2) return 0;
	int tmp, current = 1, last = 0;
	for (int i = 2; i <= n; i++) {
		tmp = current;
		current += last;
		last = tmp;
	}
	return current;
}

int cnt_fibo_iter(int n) {
	if (n < 2) return n;
	int current = 0;
	for (int i = 2; i <= n; i++) {
		current += 2;
	}

	return current;
}

int main() {
	unsigned long sum;
	int arr[8] = { 10, 15, 20, 25, 30, 35, 40, 45 };
	clock_t start, end;
	for (int i = 0; i < 8; i++) {
		start = clock();
		sum = cnt_fibo_iter(arr[i]);
		end = clock();
		printf("cnt_fibo_iter(%d) loop = %d time = %.3gsecs\n", arr[i], sum, (double)(end - start) / CLOCKS_PER_SEC);
	}
	for (int i = 0; i < 8; i++) {
		start = clock();
		sum = cnt_fibo_rec(arr[i]);
		end = clock();
		printf("cnt_fibo_rec(%d) loop = %d time = %.3gsecs\n", arr[i], sum, (double)(end - start) / CLOCKS_PER_SEC);
	}
	return 0;

}