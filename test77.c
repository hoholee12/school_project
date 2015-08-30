#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>


int main(int argc, char *argv[]){
	int fd1, fd2;

	fd1=open("test", O_RDONLY);
	fd2=open("test2", O_WRONLY);
	printf("%d %d\n", fd1, fd2); // 0=stdin 1=stdout 2=stderr 3=fd1 4=fd2


	close(fd1);
	close(fd2);



	return errno;
}
