#include<stdio.h>
#include<string.h>

typedef struct _time {
	int seconds;
	int minutes;
	int hours;



} _time;


void swaptime(_time *swap1, _time *swap2) {
	_time temp = { 0 };
	memcpy(&temp, swap1, sizeof(_time));
	memcpy(swap1, swap2, sizeof(_time));
	memcpy(swap2, &temp, sizeof(_time));
}

void swap(int *a, int *b) {
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;


}

int main() {
	_time time[3] = { 0 };
	int i, temp;
	int time_sum[3] = { 0 };
	for (i = 0; i < 2; i++) {
		printf("Enter hours, minutes and seconds respectively: ");
		scanf("%d %d %d", &time[i].hours, &time[i].minutes, &time[i].seconds);
		time_sum[i] = time[i].hours * 3600 + time[i].minutes * 60 + time[i].seconds;

	}
	if (time_sum[0] < time_sum[1]) {
		swaptime(&time[0], &time[1]);
		swap(&time_sum[0], &time_sum[1]);
	}
	time_sum[2] = time_sum[0] - time_sum[1];
	time[2].hours = time_sum[2] / 3600;
	temp = time_sum[2] % 3600;
	time[2].minutes = temp / 60;
	time[2].seconds = temp % 60;


	printf("TIME DIFFERENCE: %d:%d:%d - %d:%d:%d = %d:%d:%d\n",
		time[0].hours, time[0].minutes, time[0].seconds,
		time[1].hours, time[1].minutes, time[1].seconds,
		time[2].hours, time[2].minutes, time[2].seconds);


	return 0;
}