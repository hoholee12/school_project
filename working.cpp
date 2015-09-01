#include<stdlib.h>
#include<stdio.h>
#include<string.h> //memcpy
#include<iostream>
#include<errno.h>
#include<assert.h>
#include<getopt.h>
#define BUFSIZE 1024

int main(int argc, char *argv[]){
	int opt;
	FILE *in, *out;
	char buf[BUFSIZE];
	if(argc==1){
		printf("no input files.\n");
		exit(1);
	}
	while((opt=getopt(argc, argv, "i:o:"))!=-1){
		switch(opt){
			case 'i': if ((in=fopen(optarg, "rb"))==NULL) perror("input"); break;
			case 'o': if ((out=fopen(optarg, "wb"))==NULL) perror("output"); break;
		}

	}
	if(in==NULL){
		printf("no input io\n");
		exit(1);
	}else if(out==NULL){
		printf("no output io\n");
		exit(1);
	}
	//char c;
	//while((c=fgetc(in))!=EOF) fputc(c, out);
	assert(in!=NULL);
	assert(out!=NULL);
	int n;
	while((n=fread(buf, sizeof(char), BUFSIZE, in))>0){
		fwrite(buf, sizeof(char), BUFSIZE, out);
	}



	fclose(in);
	fclose(out);

	return 0;
}
