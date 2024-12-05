#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define ID(i,j) (i+j*100)


int is_sorted(int *array, int len, char *order) {
	for (int i = 0; i < len; ++i) {
		for (int j = i+1; j < len; ++j) {
			int val_1 = array[i];
			int val_2 = array[j];
			if (order[ID(val_2,val_1)]) return 0;
		}
	}
	return 1;
}


int main() {

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;
	}

	unsigned char *orders = calloc(100*100, 1);

	char buffer[128];
	int i = 0, j = 0;
	while (fgets(buffer,128,file) && buffer[0] != '\n') {
		sscanf(buffer, "%d|%d\n", &i, &j);
		orders[ID(i,j)] = 1;
	}
	
	int sum = 0;

	int len = 0;
	int array[64];
	while (fgets(buffer,128,file) && isdigit(buffer[0])) {
		len = 0;
		while (isdigit(buffer[3*len])) {
			sscanf(buffer+3*len, "%d", array+len);
			++len;
		}

		if (!is_sorted(array, len, orders)) continue;
		sum += array[len/2];

	}

	printf("sum: %d\n", sum);

	fclose(file);
	free(orders);
	return 0;

}
