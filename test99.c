/*written by 이정호 in nov.2015*/
/*semi-finished product after all the fucking headaches ive been thru and all the hours ive wasted:3*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define global_buffer 1024

typedef struct _test{
	char **vartype;
	char **varname;
	/*count stuff*/
	int variables;
	int comments;
	int structs;
}_test;


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
		option->varname = malloc(2*sizeof*option);
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
				pstr = strtok(NULL, " =");
				if (pstr) {
					for (l = 0, j = 0; pstr[l]; l++, j++) { /*check if its a garbage*/
						if (pstr[l] != '_'&&!isalnum(pstr[l])) {
							break;
						}

					}
					if (l == j) {
						varname_input(options, pstr);
						options->variables++;
					}
				}
				break;
			}
		}
	}
}


void parser(FILE *myfiles, _test *options, char **lines, int *eofmark, int *j, int *k) {
	int i, check, l, bc, check2;
	char *pstr = NULL;
	char str[global_buffer] = { 0 }, str2[global_buffer] = { 0 };
	*lines = malloc(sizeof*lines);
	bc = 0; check2 = 0;
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
			if (str[i] != '_' && !isalnum(str[i]) && str[i]!='#' && str[i]!='<' && str[i] != '>' && str[i] != '/' && str[i] != '*'&& !check2) /*remove header, left side, right side*/
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
			else if (strstr(str, "//")) { /*found a line comment*/
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
	int i, j, k;
	char c;
	int eofmark;
	int clearindex;
	i = 0;
	buffer = calloc(global_buffer, sizeof*buffer);
	do{
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
		printf("filename no.%d: ", i);
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
	for (i = 0; i < clearindex; i++) {
		printf("%s\n%dcomments, %dstructs, and %dvariables\n", lines[i], options->comments, options->structs, options->variables);
		for (j = 0; options->vartype[j] != -1; j++) {
			printf("%s\n", options->vartype[j]);
		
		}
	}

	/*free*/
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


	getchar();

	return 0;
}