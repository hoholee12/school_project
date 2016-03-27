#include<stdio.h>
#include<time.h>


int fibo_rec(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibo_rec(n - 1) + fibo_rec(n - 2);
}

int cnt_fibo_rec(int n, int *rec_count) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else {
		(*rec_count) += 3;
		return cnt_fibo_rec(n - 1, rec_count) + cnt_fibo_rec(n - 2, rec_count); //덧셈 3
	}
}

int fibo_iter(int n) {
	if (n < 2) return n;
	int tmp, current = 1, last = 0;
	for (int i = 2; i <= n; i++) {
		tmp = current;
		current += last;
		last = tmp;
	}

	return current;
}

int cnt_fibo_iter(int n, int* iter_count) {
	if (n < 2) return n;
	int tmp, current = 1, last = 0;
	for (int i = 2; i <= n; i++) { //덧셈
		tmp = current;
		current += last; //덧셈
		last = tmp;
		(*iter_count)+=2;
	}
	return current;
}


int main() {
	unsigned long sum;
	int rec_count = 0, iter_count = 0;
	int arr[8] = { 10, 15, 20, 25, 30, 35, 40, 45 };
	clock_t start, end;

	for (int i = 0; i < 8; i++) {
		iter_count = 0;
		start = clock();
		sum = cnt_fibo_iter(arr[i], &iter_count);
		end = clock();
		printf("cnt_fibo_iter(%d) loop = %d sum = %ld time = %.3gsecs\n", arr[i], iter_count, sum, (double)(end - start) / CLOCKS_PER_SEC);
	}
	for (int i = 0; i < 8; i++) {
		rec_count = 0;
		start = clock();
		sum = cnt_fibo_rec(arr[i], &rec_count);
		end = clock();
		printf("cnt_fibo_rec(%d) loop = %d sum = %ld time = %.3gsecs\n", arr[i], rec_count, sum, (double)(end - start) / CLOCKS_PER_SEC);
	}
	return 0;

}