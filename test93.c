#include<stdio.h>
#include<string.h>

/*string will never be empty on fgets: so "x[-1]=0" will never happen!*/
#define fgets(x, y, z) do{\
		fgets(x, y, z);\
		x[strlen(x)-1]=0;\
} while(0)

typedef struct books {
	char title[50];
	char author[50];
	char subject[100];
	int id;

} books;

int main() {
	books mybook = { 0 };
	printf("Book 1 title : ");
	fgets(mybook.title, 50, stdin);
	printf("Book 1 author : ");
	fgets(mybook.author, 50, stdin);
	printf("Book 1 subject : ");
	fgets(mybook.subject, 100, stdin);
	printf("Book 1 id : ");
	scanf("%d", &mybook.id);

	printf("[ %s, %s, %s, %d]\n", mybook.title, mybook.author, mybook.subject, mybook.id);



	return 0;
}