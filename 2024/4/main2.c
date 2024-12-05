#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char *XMAS = "XMAS";
const int dpos[16] = {
	-1,-1,
	 0,-1,
	 1,-1,
	-1, 0,
	 1, 0,
	-1, 1,
	 0, 1,
	 1, 1
};


struct StringMat {
	int w;
	int h;
	char *data;
};
typedef struct StringMat StringMat;

StringMat *createStringMat(int w, int h) {
	StringMat *mat = malloc(sizeof(StringMat));
	mat->w = w;
	mat->h = h;
	mat->data = malloc(h*(w+1) * sizeof(char));
	return mat;
}

void freeStringMat(StringMat *mat) {
	free(mat->data);
	free(mat);
}


int checkX_MAS_top(StringMat *mat, int x, int y) {
	return mat->data[(x-1)+(y-1)*(mat->w+1)] == 'M'
		&& mat->data[(x+1)+(y-1)*(mat->w+1)] == 'M'
		&& mat->data[(x-1)+(y+1)*(mat->w+1)] == 'S'
		&& mat->data[(x+1)+(y+1)*(mat->w+1)] == 'S';
}

int checkX_MAS_bottom(StringMat *mat, int x, int y) {
	return mat->data[(x-1)+(y-1)*(mat->w+1)] == 'S'
		&& mat->data[(x+1)+(y-1)*(mat->w+1)] == 'S'
		&& mat->data[(x-1)+(y+1)*(mat->w+1)] == 'M'
		&& mat->data[(x+1)+(y+1)*(mat->w+1)] == 'M';
}

int checkX_MAS_left(StringMat *mat, int x, int y) {
	return mat->data[(x-1)+(y-1)*(mat->w+1)] == 'M'
		&& mat->data[(x+1)+(y-1)*(mat->w+1)] == 'S'
		&& mat->data[(x-1)+(y+1)*(mat->w+1)] == 'M'
		&& mat->data[(x+1)+(y+1)*(mat->w+1)] == 'S';
}

int checkX_MAS_right(StringMat *mat, int x, int y) {
	return mat->data[(x-1)+(y-1)*(mat->w+1)] == 'S'
		&& mat->data[(x+1)+(y-1)*(mat->w+1)] == 'M'
		&& mat->data[(x-1)+(y+1)*(mat->w+1)] == 'S'
		&& mat->data[(x+1)+(y+1)*(mat->w+1)] == 'M';
}


int main() {
	StringMat *mat = createStringMat(140,140);

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	for (int i = 0; i < mat->h; ++i) {
		char *res = fgets(mat->data+(mat->w+1)*i, mat->w+1, file);
		(char)fgetc(file);
	}
	fclose(file);

	int n = 0;
	for (int i = 1; i < mat->w-1; ++i) {
		for (int j = 1; j < mat->h-1; ++j) {
			if (mat->data[i+j*(mat->w+1)] != 'A') continue;
			if (checkX_MAS_top(mat, i,j)) ++n;
			if (checkX_MAS_bottom(mat, i,j)) ++n;
			if (checkX_MAS_left(mat, i,j)) ++n;
			if (checkX_MAS_right(mat, i,j)) ++n;
		}
	}

	printf("n: %d\n", n);
	freeStringMat(mat);
	return 0;

}
