#include <stdio.h>
#include <stdlib.h>



int checkReport(int *vals, int len) {
	int direction = vals[0] < vals[1];
	for (int j = 0; j < len-1; ++j) {
		int diff = abs(vals[j] - vals[j+1]);
		if (vals[j] < vals[j+1] != direction || diff == 0 || diff > 3) {
			return 0;
		}
	}
	return 1;
}



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
	while (getline(&line, &size, file) != -1) {
		char *ptr = line;

		int i = 0;
		while (sscanf(ptr, "%d", vals+i) != EOF) {
			++i;
			while (*ptr != ' ' && *ptr != '\n') ptr++;
			if (*ptr == ' ') ptr++;
			if (*ptr == '\n') break;
		}

		if (checkReport(vals, i)) sum++;
		else {
			for (int skip = 0; skip < i; ++skip) {
				int new_vals[16];
				int j = 0;
				for (int k = 0; k < i; k++) {
					if (k == skip) continue;
					new_vals[j++] = vals[k];
				}
				if (checkReport(new_vals, i-1)) {
					++sum;
					break;
				}
			}
		}

	}

	printf("valid: %d\n", sum);

	free(line);
	return 0;

}