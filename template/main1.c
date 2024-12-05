#include <stdio.h>
#include <stdlib.h>


int main() {

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	fclose(file);
	return 0;

}
