.PHONY: all 
all: part1

.PHONY: run 
run: part1
	./$^

part1: main1.c
	gcc $^ -o $@ -O3

.PHONY: clean
clean:
	rm -f *.o
	rm -f part1
