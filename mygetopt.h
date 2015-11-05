/*created by hoholee12*/

#pragma once
#include<stdio.h>
#include<stdlib.h> /*exit*/

#define swap(x, y) do{\
	x = x + y;\
	y = x - y;\
	x = x - y;\
 } while (0);

typedef struct _optstuff {
	int on;
	char name;
	char *optarg;
} _optstuff;
typedef struct _optarr {
	_optstuff **arr;


} _optarr;


void error(int argc, char **argv, char *opt, char *msg) {


	fprintf(stderr, "%s: %s -%s.\n", argv[0], msg, opt);
	exit(1);
}


void mygetopt(int argc, char **argv, char *delim, _optarr *optarr) {
	int i, j, k, l;
	for (i = 1; i<argc; i++) {

		if (argv[i][0] != '-') continue; /*skip if its not an optarg parameter*/




		for (k = 0; optarr->arr[k]; k++); /*throw exception when bullshit entered - loop*/
		for (j = 0; optarr->arr[j]; j++) { /*main stuff*/
			if (optarr->arr[j]->name == argv[i][1]) {


				if (optarr->arr[j]->on == 1) {
					error(argc, argv, argv[i], "same option");
				}
				else {
					optarr->arr[j]->on = 1;
					/********************************************************************************************************/
					for(l=0; (delim[l]!=optarr->arr[j]->name)&&delim[l]; l++); /*if the option has optarg according to delim*/
					
					if (delim[l + 1] == ':') {
							
						if(argc>i+1){
							if (argv[i + 1][0] != '-')optarr->arr[j]->optarg = argv[i + 1];
							else error(argc, argv, argv[i], "option requires an argument");
						}
						else error(argc, argv, argv[i], "option requires an argument");
					}
					else {
						if(argc>i+1){
							if (argv[i + 1][0] != '-') error(argc, argv, argv[i], "option does not require an argument");
						}
						
					}
					/********************************************************************************************************/

					
				}

				break;
			}


		}
		if (k == j) { /*throw exception when bullshit entered - check*/
			error(argc, argv, argv[i], "unknown option");

		}

	}

}