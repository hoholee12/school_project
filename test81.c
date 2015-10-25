#include<stdarg.h>
#include<stdio.h>

void print_arguments(int number_of_arguments, ...)
{
  va_list list;
  va_start(list, number_of_arguments);
  printf("I am first element of the list: %d \n", va_arg(list, int));
  printf("I am second element of the list: %d \n", va_arg(list, int));
  printf("I am third element of the list: %d \n", va_arg(list, int));
  va_end(list);
}

int main(){
	
	print_arguments(3,1,2,3);
	return 0;
	
}