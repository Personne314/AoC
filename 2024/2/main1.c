#include <stdio.h>
#include <stdlib.h>



int main() {

	size_t size = 64;
	char *line = malloc(sizeof(int)*size);

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	int vals[16];

	int sum = 0;
	int nv_sum = 0;
	while (getline(&line, &size, file) != -1) {
		char *ptr = line;
		++sum;

		int i = 0;
		while (sscanf(ptr, "%d", vals+i) != EOF) {
			++i;
			while (*ptr != ' ' && *ptr != '\n') ptr++;
			if (*ptr == ' ') ptr++;
			if (*ptr == '\n') break;
		}

		int direction = vals[0] < vals[1];
		for (int j = 0; j < i-1; ++j) {
			int diff = abs(vals[j] - vals[j+1]);
			if (vals[j] < vals[j+1] != direction || diff == 0 || diff > 3) {
				++nv_sum;
				break;
			}
		}

	}

	printf("valid: %d\n", sum-nv_sum);

	free(line);
	return 0;

}