#include <stdio.h>
#include <stdlib.h>


enum Dir {
	UP,
	LEFT,
	DOWN,
	RIGHT
};
typedef enum Dir Dir;

const int dpos[4][2] = {
	{0,-1},
	{1,0},
	{0,1},
	{-1,0}
};


Dir nextDir(Dir dir) {
	return (dir+1)%4;
}


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


#define AT(mat, x, y) (mat->data[x+(mat->w+1)*y])



int move(StringMat *mat, int *c_x, int *c_y, Dir *dir) {
	char c = AT(mat, *c_x,*c_y);

	switch (c) {
	case '#':
		*c_x -= dpos[*dir][0];
		*c_y -= dpos[*dir][1];
		*dir = nextDir(*dir);
		return 0;
	case '.':
		AT(mat, *c_x,*c_y) = 'X';
		*c_x += dpos[*dir][0];
		*c_y += dpos[*dir][1];
		return 1;
	case 'X':
		*c_x += dpos[*dir][0];
		*c_y += dpos[*dir][1];
		return 0;
	}
	return 0;

}

int main() {

	StringMat *mat = createStringMat(130,130);

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	Dir dir = UP;
	int c_x, c_y;
	for (int i = 0; i < mat->h; ++i) {
		char *res = fgets(mat->data+(mat->w+1)*i, mat->w+1, file);
		(char)fgetc(file);
		for (int j = 0; j < mat->w; ++j) {
			if (AT(mat, j, i) == '^') {
				c_x = j;
				c_y = i;
			}
		}
	}
	fclose(file);

	int sum = 1;
	AT(mat, c_x, c_y) = 'X';
	while (c_x >= 0 && c_y >= 0 && c_x < mat->w && c_y < mat->h) {
		if (move(mat, &c_x, &c_y, &dir)) ++sum;
	}

	printf("%d\n", sum);

	return 0;

}
