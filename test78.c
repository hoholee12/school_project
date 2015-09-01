#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h> //size_t, ssize_t, pid_t

main(){
	int fd1, fd2;
	ssize_t n;
/*
	these are portable and said to be faster than int counterparts:

	size_t == unsigned int, use it to return a size in bytes
	ssize_t == signed int, use it to return a size in bytes or return negative value
	pid_t == signed int, for pid stuff

*/

	char buf[BUFFSIZE];



}
