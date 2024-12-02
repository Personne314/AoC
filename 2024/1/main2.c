#include <stdio.h>
#include <stdlib.h>


int main() {

	char *list1 = calloc(100000, 1);
	char *list2 = calloc(100000, 1);

	FILE *file = fopen("./input", "r");
	if (file) {

		int n1 = 0;
		int n2 = 0;
		while (fscanf(file, "%d   %d\n", &n1, &n2) != EOF) {
			++list1[n1];
			++list2[n2];
		}
		fclose(file);

		int i = 0;
		int sum = 0;
		while (i < 100000) {
			sum += list1[i]*i*list2[i];
			++i;
		}

		printf("sum: %d\n", sum);

	} else {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;
	}

	free(list1);
	free(list2);
	
	return 0;

}
