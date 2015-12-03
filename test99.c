/*written by 이정호 in nov.2015*/
/*semi-finished product after all the f**king headaches ive been thru and all the hours ive wasted:3*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define global_buffer 1024
#define DEBUG

typedef struct _test {
	char **vartype;
	char **varname;
	/*count stuff*/
	int variables;
	int comments;
	int structs;
}_test;


#define printf(x, ...) do{printf(x,##__VA_ARGS__);fflush(stdout);}while(0)

char *sanitize(char *line) {
	int i;
	for (i = 0; line[i + 1]; i++);
	if (line[i] == '\n') line[i] = 0;
	return line;
}

void error(char *err, int errcode) {
	fputs(err, stderr);
	exit(errcode);
}


void varname_input(_test *option, char *str) {
	int i;
	if (!option->varname) {
		option->varname = malloc(2 * sizeof*option);
		option->varname[0] = calloc(63, sizeof*option);
		option->varname[1] = -1;
		strncpy(option->varname[0], str, 63);
		return;
	}
	for (i = 0; option->varname[i] != -1; i++);
	option->varname = realloc(option->varname, (i + 2)*sizeof*option);
	option->varname[i] = calloc(63, sizeof*option);
	option->varname[i + 1] = -1;
	strncpy(option->varname[i], str, 63);
}

void vartype_input(_test *option, char *str) {
	int i;
	if (!option->vartype) {
		option->vartype = malloc(2 * sizeof*option);
		option->vartype[0] = calloc(63, sizeof*option);
		option->vartype[1] = -1;
		strncpy(option->vartype[0], str, 63);
		return;
	}
	for (i = 0; option->vartype[i] != -1; i++);
	option->vartype = realloc(option->vartype, (i + 2)*sizeof*option);
	option->vartype[i] = calloc(63, sizeof*option);
	option->vartype[i + 1] = -1;
	strncpy(option->vartype[i], str, 63);
}

void details(FILE *myfiles, _test *options, char *lines, int *eofmark) {
	char str[global_buffer] = { 0 }, str2[global_buffer] = { 0 };
	char *pstr = NULL, *pstrb = NULL;
	int i, check, l, j, k;
	/*c type*/
	vartype_input(options, "char");
	vartype_input(options, "short");
	vartype_input(options, "int");
	vartype_input(options, "long");
	vartype_input(options, "long long");
	vartype_input(options, "float");
	vartype_input(options, "double");
	vartype_input(options, "void");
	/*checking stuff*/
	fseek(myfiles, 0, SEEK_SET);
	while (fgets(str2, global_buffer, myfiles)) {
		/*remove trailing newline*/
		memset(str, 0, global_buffer*sizeof*str);
		for (i = 0, l = 0; (check = str2[i]); i++) {
			switch (check) {
			case '\n': break;
			case '\t': break;
			case ';': break;
			default: str[l++] = str2[i];
			}
		}
		/*struct type*/
		if ((pstr = strstr(str, "typedef struct"))) {
			do {
				memset(str, 0, global_buffer*sizeof*str);
				for (i = 0, l = 0; (check = str2[i]); i++) {
					switch (check) {
					case '\n': break;
					case '\t': break;
					case ';': break;
					default: str[l++] = str2[i];
					}
				}
				if ((pstr = strstr(str, "}"))) {
					pstr = strtok(pstr, " }");
					break;
				}
			} while (fgets(str2, global_buffer, myfiles));
			vartype_input(options, pstr);
			options->structs++;
			continue;
		}


		if ((pstrb = strstr(str, "typedef"))) {
			pstrb = strtok(pstrb, " ");
			while (pstrb) {
				if (pstrb) pstr = pstrb;
				pstrb = strtok(NULL, " ");
			}
			vartype_input(options, pstr);
		}

		/*find varname*/
		if ((pstr = strstr(str, "#define"))) {
			strtok(pstr, " ");
			pstr = strtok(NULL, " ");
			varname_input(options, pstr);
			options->variables++;
			continue;
		}

		if ((pstr = strstr(str, "struct"))) {
			if (!strstr(pstr, "=")) {
				do {
					memset(str, 0, global_buffer*sizeof*str);
					for (i = 0, l = 0; (check = str2[i]); i++) {
						switch (check) {
						case '\n': break;
						case '\t': break;
						case ';': break;
						default: str[l++] = str2[i];
						}
					}
					if ((pstr = strstr(str, "}"))) {
						pstr = strtok(pstr, " }");
						break;
					}
				} while (fgets(str2, global_buffer, myfiles));
				options->structs++;
				continue; /*lets not care about struct stuff for now.*/
			}
			strtok(pstr, " ");
			strtok(NULL, " ");
			pstr = strtok(NULL, " =");
			varname_input(options, pstr);
			options->variables++;
			continue;
		}

		for (i = 0; options->vartype[i] != -1; i++) {
			if ((pstr = strstr(str, options->vartype[i]))) {
				if (strstr(pstr, "(")) break;
				strtok(pstr, " ");
				pstr = strtok(NULL, "=");
				if (pstr) {
					pstr = strtok(pstr, ", ");
					do {
						varname_input(options, pstr);
						options->variables++;
					} while ((pstr = strtok(NULL, ", "))); /*if it finds comma, it means im scanning a parameter*/
				}
				break;
			}
		}
	}
}


void parser(FILE *myfiles, _test *options, char **lines, int *eofmark, int *j, int *k) {
	int i, check, l, bc, check2, check3, check4;
	char *pstr = NULL;
	char str[global_buffer] = { 0 }, str2[global_buffer] = { 0 };
	*lines = malloc(sizeof*lines);
	bc = 0; check2 = 0, check3 = 0, check4 = 0;
	while (fgets(str2, global_buffer, myfiles)) {
		/*remove trailing newline & tabs*/
		memset(str, 0, global_buffer*sizeof*str);
		for (i = 0, l = 0; (check = str2[i]); i++) {
			switch (check) {
			case '\n': break;
			case '\t': break;
			case ' ': break;
			case ';': break;
			default: str[l++] = str2[i];
			}
		}


		*k += strlen(str);
		*lines = realloc(*lines, (*k + 1)*sizeof*lines);
		/*remove alphabet and underscore*/
		for (i = 0, l = bc; i < strlen(str); i++) {
			if (str[i] == '"') { /*found a string*/
				if (!check3)
					check3 = 1;
				else
					check3 = 0;
				continue;
			}

			if (str[i] == '\'') { /*found a character*/
				if (!check4)
					check4 = 1;
				else
					check4 = 0;
				continue;
			}

			/*truncate logic & final output*/
			if (
				str[i] != '.' &&
				 str[i] != '=' &&
				  str[i] != '_' &&
				   !isalnum(str[i]) &&
				    str[i] != '#' &&
				     str[i] != '<' &&
				      str[i] != '>' &&
				       str[i] != '/' &&
				        str[i] != '*'&&
				         !check2 && !check3 && !check4) /*remove what you want to remove here to gain more detection rate*/
				(*lines)[l++] = str[i];


			if (strstr(str, "/*")) { /*found a comment*/
				if (!strstr(str, "*/")) {
					check2 = 1;
					break;
				}
				options->comments++;
				break;
			}
			if (check2&&strstr(str, "*/")) {
				check2 = 0;
				options->comments++;
			}
			if (strstr(str, "//")) { /*found a line comment*/
				options->comments++;
				break;
			}
		}



		(*lines)[l] = 0;
		bc = l;
	}


}


int main() {
	FILE **myfiles = NULL;
	char **buffer = NULL;
	char **lines = NULL;
	_test *options = NULL;
	char **diffcheck = NULL;
	int i, j, k, l, m;
	char c;
	int eofmark;
	int clearindex;
	int flag;
	i = 0;
	buffer = calloc(global_buffer, sizeof*buffer);
	do {
		if (!myfiles) {
			printf("main file to compare: ");
			buffer[0] = calloc(global_buffer, sizeof*buffer);
			fgets(buffer[0], global_buffer, stdin);
			if (buffer[0][0] == '\n') break;
			myfiles = malloc(sizeof*myfiles);
			lines = malloc(sizeof*lines);
			lines = memset(lines, 0, sizeof*lines);
			options = malloc(sizeof*options);
			options = memset(options, 0, sizeof*options);
			myfiles[0] = fopen(sanitize(buffer[0]), "r");
			if (!myfiles[0]) error("not a valid file\n", 1);
			continue;
		}
		printf("filename no.%d:(hit return key again to start comparing) ", i);
		buffer[i] = calloc(global_buffer, sizeof*buffer);
		fgets(buffer[i], global_buffer, stdin);
		if (buffer[i][0] == '\n') break;
		myfiles = realloc(myfiles, (i + 1)*sizeof*myfiles);
		lines = realloc(lines, (i + 1)*sizeof*lines);
		lines = memset(lines, 0, (i + 1)*sizeof*lines);
		options = realloc(options, (i + 1)*sizeof*options);
		options = memset(options, 0, (i + 1)*sizeof*options);
		myfiles[i] = fopen(sanitize(buffer[i]), "r");
		if (!myfiles[i]) error("not a valid file\n", 1);
	} while (++i);
	clearindex = i;
	if (!myfiles) error("nothing entered!\n", 1);

	/*main*/
	for (i = 0; i < clearindex; i++) {
		j = 0, k = 0, eofmark = 0;
		parser(myfiles[i], &options[i], &lines[i], &eofmark, &j, &k);
		details(myfiles[i], &options[i], &lines[i], &eofmark);
	}

	/*test*/
#ifdef DEBUG
	printf("main file logic: %s\n"
		"=========================================================\n"
		, lines[0]);
#endif
	for (i = 1; i < clearindex; i++) {
		printf(
			"filename: %s\n"
#ifdef DEBUG
			"logic: %s\n"
#endif
			"=========================================================\n"
			, buffer[i]
#ifdef DEBUG
			, lines[i]
#endif
			);

		l = 0;
		m = 0; /*check whether variable naming is different*/
		diffcheck = malloc(sizeof*diffcheck);
		for (j = 0; options[0].varname[j] != -1 && options[i].varname[j] != -1; j++) {
			if (strcmp(options[0].varname[j], options[i].varname[j])) {
				diffcheck = realloc(diffcheck, (l + 2)*sizeof*diffcheck);
				diffcheck[l] = calloc(63, sizeof*diffcheck);
				diffcheck[l + 1] = -1;
				strcpy(diffcheck[l++], options[i].varname[j]);
				m = 1;
			}


		}

		flag = 0;
		if (!strcmp(lines[0], lines[i])) {
			if (
				options[0].comments != options[i].comments||
				options[0].structs != options[i].structs||
				options[0].variables != options[i].variables
				){
				if (options[i].comments < options[0].comments)
					printf("%d less comments, ", options[0].comments - options[i].comments);
				else printf("%d more comments, ", options[i].comments - options[0].comments);

				if (options[i].structs < options[0].structs)
					printf("%d less structs, ", options[0].structs - options[i].structs);
				else printf("%d more structs, ", options[i].structs - options[0].structs);

				if (options[i].variables < options[0].variables)
					printf("%d less variables found\n", options[0].variables - options[i].variables);
				else printf("%d more variables found\n", options[i].variables - options[0].variables);
			}
			else flag = 1;
				if (m) {
					printf("variable differences found!:\n");
					for (l = 0; diffcheck[l] != -1; l++) {
						printf("%d: %s\n", l + 1, diffcheck[l]);
					}

				}
				if (flag)
					printf(
						"=========================================================\n"
						"%s and %s are LITERALLY identical.\n"
						"PLAGIARISM CONFIRMED!!!1!!!11\n"
						, buffer[0], buffer[i]);
				else
					printf(
						"=========================================================\n"
						"%s and %s are *logically* identical.\n"
						"PLAGIARISM CONFIRMED!!!1!!!11\n"
						, buffer[0], buffer[i]);
		}
		else printf("no plagiarism detected.\n");

		printf("\n");
	}

	/*free*/
	for(j=0;diffcheck[j]!=-1;j++){
		free(diffcheck[j]);
	}
	free(diffcheck);
	if (myfiles) {
		free(myfiles);
		for (i = 0; i < clearindex; i++) {
			free(lines[i]);
			free(buffer[i]);
		}
		free(lines);
		free(buffer);
		free(options);
	}

	printf("hit return key to continue...");
	getchar();

	return 0;
}