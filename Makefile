CC := gcc
CFLAGS := -std=c23 -O3
DEBUGFLAGS := -Wall -Wextra -Wpedantic -fsanitize=address -g -fanalyzer -std=c23

.PHONY: clean debug

clean:
	rm -f yabi debug
debug: main.c utils/stack.c
	$(CC) $^ -o $@ $(DEBUGFLAGS)

.DEFAULT_GOAL := yabi
yabi: main.c utils/stack.c
	$(CC) $^ -o $@ $(CFLAGS)
