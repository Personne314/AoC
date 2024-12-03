#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *file = fopen("input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open input file\n");
		return 1;
	}

	int n = 0;
	int l = 0;

	char str[1024];
	while (fgets(str, 1024, file)) {

		int i = 0;
		while (str[i]) {
			if (str[i] == '(') n++;
			if (str[i] == ')') n--;

			if (n == -1) printf("%d\n", i+l*1024);

			++i;
		}

		l++;

	}

	printf("n: %d\n", n);

}
