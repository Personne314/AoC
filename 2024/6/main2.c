#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int dirFlag(Dir dir) {
	switch (dir) {
	case UP:	return 0b00000001;
	case LEFT:	return 0b00000010;
	case DOWN:	return 0b00000100;
	case RIGHT:	return 0b00001000;
	}
}


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

void move_check(StringMat *mat, int *c_x, int *c_y, Dir *dir) {
	char c = AT(mat, *c_x,*c_y);

	switch (c) {
	case '#':
		*c_x -= dpos[*dir][0];
		*c_y -= dpos[*dir][1];
		*dir = nextDir(*dir);
		return;
	case '.':
		AT(mat, *c_x,*c_y) = AT(mat, *c_x,*c_y)|dirFlag(*dir);
		*c_x += dpos[*dir][0];
		*c_y += dpos[*dir][1];
		return;
	default:
		*c_x += dpos[*dir][0];
		*c_y += dpos[*dir][1];
	}

}


int check(StringMat *mat, int *p_x, int *p_y, int o_i, int o_j) {
	int c_x = *p_x;
	int c_y = *p_y;

	StringMat *mat_cp = createStringMat(mat->w, mat->h);
	for (int i = 0; i < mat->w; ++i) {
		for (int j = 0; j < mat->h; ++j) {
			if (AT(mat, i,j) == '#') AT(mat_cp, i,j) = '#';
			else AT(mat_cp, i,j) = '.';
		}
	}
	AT(mat_cp, o_i, o_j) = '#';

	Dir dir = UP; 
	int i = 10000;
	while (c_x >= 0 && c_y >= 0 && c_x < mat_cp->w && c_y < mat_cp->h) {
		if (i == 0) {
			freeStringMat(mat_cp);
			return 1;
		}
		move(mat_cp, &c_x, &c_y, &dir);
		--i;
	}
	freeStringMat(mat_cp);
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

	int start_x = c_x;
	int start_y = c_y;
	AT(mat, c_x, c_y) = 'X';
	while (c_x >= 0 && c_y >= 0 && c_x < mat->w && c_y < mat->h) {
		move(mat, &c_x, &c_y, &dir);
	}

	
	StringMat *mat_cp = createStringMat(mat->w, mat->h);
	memcpy(mat_cp->data, mat->data, (mat->w+1)*mat->h);

	int sum = 0;
	for (int i = 0; i < mat->w; ++i) {
		for (int j = 0; j < mat->h; ++j) {
			if (AT(mat, i,j) != 'X') continue;
			if (check(mat, &start_x, &start_y, i,j)) {
				sum++;
				AT(mat_cp,i,j) = 'O';
			}
		}	
	}
	printf("%d\n", sum);
	freeStringMat(mat);
	return 0;

}
