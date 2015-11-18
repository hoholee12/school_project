#include<stdio.h>

typedef enum _genre {
	UNDEFINED,
	DRAMA,
	ACTION,
	SF,
	ANIMATION,
	THRILLER,
	COMEDY
} _genre;

typedef struct movie {
	char title[30];
	char director[20];
	float score;
	char actor[20];
	char actress[20];
	_genre genre;
} movie;

int movie_equal(movie m1, movie m2) {
	if (strcmp(m1.title, m2.title)) return 0;
	if (strcmp(m1.director, m2.director)) return 0;
	if (m1.score != m2.score) return 0;
	if (strcmp(m1.actor, m2.actor)) return 0;
	if (strcmp(m1.actress, m2.actress)) return 0;
	if (m1.genre != m2.genre) return 0;
	return 1;
}

void printmovie(movie *p) {
	printf("%s %s %f %s %s genre:", p->title, p->director, p->score, p->actor, p->actress);
	switch (p->genre) {
	case UNDEFINED: printf("undefined\n"); break;
	case DRAMA: printf("drama\n"); break;
	case ACTION: printf("action\n"); break;
	case SF: printf("science fiction\n"); break;
	case ANIMATION: printf("animation\n"); break;
	case THRILLER: printf("thriller\n"); break;
	case COMEDY: printf("comedy\n"); break;
	}
}

/*arrays and structures are different!!!
	array: int **arr => arr[][]
	structure: struct *arr => arr[].stuff (no **arr)

*/
movie* highest_score(movie *arr, int i) {
	float highestscore = arr[--i].score;
	movie *highestmovie = &arr[i];
	for (i--; i > -1; i--) {
		if (highestscore < arr[i].score) {
			highestscore = arr[i].score;
			highestmovie = &arr[i];
		}
	}
	return highestmovie;
}

int main() {
	movie movie_collect[10] = {
		{ "spiderman 3", "sam raimi", 8.8, "ravioli", "pasta", SF },
		{ "transformer", "ka boom guy", 9.9, "schlep", "meatballs", ACTION },
		{"hello", "michael", 7.7, "test", "me", THRILLER }
	};
	printmovie(highest_score(movie_collect, 10));

	return 0;
}