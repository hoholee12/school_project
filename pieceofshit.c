#include<stdio.h>
#include<time.h>
#define SIZE 100
void seed() {
	srand((unsigned)time(0));

}

int main() {
	int i, j, k, ended, tmp, array[SIZE], final;
	int x, biggest_count, biggest_rand;
	seed();

	//generate
	for (i = 0; i < SIZE; i++) {
		array[i] = rand() % 10;
	}
	//sort
	for (x = 0; x < SIZE; x++) { //to make sure everything is sorted properly
		for (i = 0; i < SIZE; i++) { //master
			for (j = 0; j < SIZE; j++) { // compare first
				if (array[i] == array[j]) {
					for (k = i; k < SIZE; k++) { //look for others to replace
						if (array[k] != array[j]) {
							tmp = array[j];
							array[j] = array[k];
							array[k] = tmp;
							break; //if found
						}
					}
				}
			}
			//i += k; //speedhack
		}
	}

	//for (i = 0; i < SIZE; i++) printf("%d\n", array[i]);
	//printf("\n\n");
	//final sort
	final = array[0];
	j = 0;//outer loop
	k = 0;// inner loop
	for (i = 1; i < SIZE; i++) {
		if (final!=array[i]) {
			array[j]=final;
			array[j + 1] = k+1;
			array[j + 2] = -1; //end of one setting
			j += 3;
			final = array[i];
			k = 0;
		}
		else k++;
	}
	array[j] = array[i - 1]; //hack
	array[j + 1] = k+1;
	array[j + 2] = -1;
	array[j + 3] = -1; //end of final loop

	biggest_rand = array[0];
	biggest_count = array[1];
	for (i = 0; i < SIZE; i+=3) {
		if (array[i] == -1) break; //end of loop
		if (array[i + 1]>biggest_count) {
			biggest_rand = array[i];
			biggest_count = array[i + 1];
		}
	}
	printf("biggest rand: %d by %d", biggest_rand, biggest_count);


	//for (i = 0; i < SIZE; i++) printf("%d\n", array[i]);
	return 0;
}