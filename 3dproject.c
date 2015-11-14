#include<windows.h>

#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<stdio.h>
#define SECS 1000


void error_callback(int error, const char *description){
	fputs(description, stderr);
}

int main(){
	GLFWwindow *window;
	if(!glfwInit()) exit(EXIT_FAILURE);
	window=glfwCreateWindow(1440, 900, "Title", NULL, NULL);
	glfwSetErrorCallback(error_callback);
	
	
	Sleep(SECS);
	glfwTerminate();
	
	return 0;
}