#include<stdlib.h>
#include<stdio.h>
#include<string.h> //memcpy
#include<iostream>

using namespace std;


int main(int argc, char *argv[]){
	FILE *in=fopen("a.out", "rb");
	fseek(in, 0L, SEEK_END);
	long size=ftell(in);
	fseek(in, 0L, SEEK_SET);
	char mem[size];
	//memcpy(mem, in, size);
	fread(mem, sizeof(char), size, in);
	fclose(in);
	FILE *out=fopen("b.out", "wb");
	//printf("%s\n", mem);
	//memcpy(out, mem, size);
	fwrite(&mem, sizeof(char), size, out);
	free(mem);
	fclose(out);
	//remove(argv[0]); this thing actually exists

	return 0;
}
