#include<windows.h>


#include"GLFW/glfw3.h"
#include<stdio.h>
#define SECS 1000


void error_callback(int error, const char *description){
	fputs(description, stderr);
}

int main(){
	if(!glfwInit()) exit(EXIT_FAILURE);
	
	glfwSetErrorCallback(error_callback);
	
	
	Sleep(SECS);
	glfwTerminate();
	
	return 0;
}