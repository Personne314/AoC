#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



const long long shift[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 
	1000000000, 10000000000LL, 100000000000LL, 1000000000000LL, 
	10000000000000LL, 100000000000000LL, 1000000000000000LL, 
	10000000000000000LL, 100000000000000000LL, 1000000000000000000LL
};


int int_size(uint64_t value) {
	char buffer[32];
	return snprintf(buffer, 32, "%ld", value);
}



uint64_t rec_evaluate(uint64_t *list, int n, uint64_t val, int i, uint64_t current_val) {
	if (i == n) return val == current_val;
	if (rec_evaluate(list, n, val, i+1, current_val+list[i+1])) return 1;
	if (rec_evaluate(list, n, val, i+1, current_val*list[i+1])) return 1;
	if (rec_evaluate(list, n, val, i+1, current_val*shift[int_size(list[i+1])]+list[i+1])) return 1;
	return 0;
}

uint64_t evaluate(uint64_t *list, int n, uint64_t val) {
	if (!rec_evaluate(list, n-1, val, 0, list[0])) return 0;
	return val;
}



int main() {

	FILE *file = fopen("./input", "r");
	if (!file) {
		fprintf(stderr, "Unable to open the input file\n");
		return 1;	
	}

	uint64_t sum = 0;

	char line[64];
	uint64_t val = 0;
	uint64_t nums[32];
	while (fgets(line, 64, file)) {
		int n = 0; 
		int d = 0;
		int pos = 0;
		sscanf(line, "%ld:%n", &val, &pos);
		while (sscanf(line+pos, " %ld%n", nums+n, &d)) {
			++n; pos += d;
			if (line[pos] == '\n' || line[pos] == '\0') break;
		}
	
		sum += evaluate(nums, n, val);

	}

	printf("%ld\n", sum);
	fclose(file);
	return 0;

}
