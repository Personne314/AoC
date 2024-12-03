#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct mul {
	int l;
	int r;
};
typedef struct mul Mul;



int parseInt(int *p_val, char *line, int *p_i) {
	*p_val = 0;
	if (!isdigit(line[*p_i])) return 0;

	int i = 0;
	while (isdigit(line[*p_i])) {
		*p_val = *p_val*10 + line[(*p_i)++]-'0';
		if (++i > 3) return 0;
	}
	return 1;
}



int parseMul(Mul *p_mul, char *line, int *p_i) {

	p_mul->l = 0;
	p_mul->r = 0;

	int state = 0;
	while(line[*p_i] != '\0' && state != 8) {
		char c = line[*p_i];

		switch (state) {
		case 0: // m
			if (c == 'm') state = 1;
			++*p_i;
			break;
		case 1: // mu
			if (c == 'u') state = 2; 
			else if (c == 'm') state = 1;
			else state = 0;
			++*p_i;
			break;
		case 2: // mul
			if (c == 'l') state = 3;
			else if (c == 'm') state = 1;
			else state = 0;
			++*p_i;
			break;
		case 3: // mul(
			if (c == '(') state = 4;
			else if (c == 'm') state = 1;
			else state = 0;
			++*p_i;
			break;
		case 4: // mul(int
			if (c == 'm') state = 0;
			else if (!parseInt(&p_mul->l, line, p_i)) state = 0;
			else state = 5; break;
		case 5: // mul(int,
			if (c == ',') state = 6;
			else if (c == 'm') state = 1;
			else state = 0;
			++*p_i;
			break;
		case 6: // mul(int,int
			if (c == 'm') state = 0;
			else if (!parseInt(&p_mul->r, line, p_i)) state = 0;
			else state = 7; break;
		case 7: // mul(int,int)
			if (c == ')') state = 8;
			else if (c == 'm') state = 1;
			else state = 0;
			++*p_i;
			break;
		}

	}
	return state == 8;

}



int main(int argc, char const *argv[]) {
	
	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	int sum = 0;
	size_t size = 0;
	char *line = NULL;
	while (getline(&line, &size, file) != -1) {

		Mul mul;
		int i = 0;
		while (parseMul(&mul, line, &i)) sum += mul.l*mul.r;

	}

	printf("sum: %d\n", sum);

	free(line);
	fclose(file);
	return 0;

}
