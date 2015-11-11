#include<stdio.h>
#include<string.h>



typedef struct books {
	char title[50];
	char author[50];
	char subject[100];
	int id;

} books;

int main() {
	books mybook = { 0 };
	printf("Book 1 title : ");
	gets(mybook.title);
	printf("Book 1 author : ");
	gets(mybook.author);
	printf("Book 1 subject : ");
	gets(mybook.subject);
	printf("Book 1 id : ");
	scanf("%d", &mybook.id);

	printf("[ %s, %s, %s, %d]\n", mybook.title, mybook.author, mybook.subject, mybook.id);



	return 0;
}