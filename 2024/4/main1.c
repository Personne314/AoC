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


int checkXMAS(StringMat *mat, int dx, int dy, int x, int y, int i) {
	if (i == 4) return 1;
	if (x < 0 || y < 0 || x >= mat->w || y >= mat->h) return 0;
	if (mat->data[x+y*(mat->w+1)] != XMAS[i]) return 0;
	return checkXMAS(mat, dx, dy, x+dx, y+dy, i+1);
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
	for (int i = 0; i < mat->w; ++i) {
		for (int j = 0; j < mat->h; ++j) {
			if (mat->data[i+j*(mat->w+1)] != 'X') continue;
			for (int k = 0; k < 8; k++) {
				if (checkXMAS(mat, dpos[2*k], dpos[2*k+1], i,j, 0)) ++n;
			}
		}
	}

	printf("n: %d\n", n);
	freeStringMat(mat);
	return 0;

}
