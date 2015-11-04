/*created by hoholee12*/

#pragma once
#include<stdio.h>



void mystrstr(char *input, char *replacefrom, char *replacewith, char *result) {
	int i, j, k, l;

	/*sanitize*/
	for (i = 0; input[i+1]; i++);
	input[i] = 0;
	for (i = 0; replacefrom[i+1]; i++);
	replacefrom[i] = 0;
	for (i = 0; replacewith[i+1]; i++);
	replacewith[i] = 0;

	
	
	for (i = 0; input[i]; i++) {
		for (k = 0; replacefrom[k]; k++); /*strlen*/
		for (j = 0; replacefrom[j]; j++) {
			if (input[i + j] != replacefrom[j]) {
				break;
			}

		}
		if (k == j) {
			break;


		} /*match!*/


	}
	k = 0;
	
	for (l = 0; input[l]; l++) {
		if (i == l) {
			for (k = 0; replacewith[k]; k++) {
				result[l + k] = replacewith[k];
			}
			k--; /*hax*/
			for (j = 0; replacefrom[j]; j++); /*strlen*/
			j--; /*hax*/
		}
		else {
			if(k) result[l + k] = input[l + j]; /*if replace occured*/
			else result[l] = input[l];
		}
	}
	result[l + k] = 0; /*end with null*/
	
}