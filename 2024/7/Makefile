.PHONY: all 
all: part1 part2

.PHONY: run 
run: part2
	./$^

part1: main1.c
	gcc $^ -o $@ -O3

part2: main2.c
	gcc $^ -o $@ -O3

.PHONY: clean
clean:
	rm -f *.o
	rm -f part1
	rm -f part2
