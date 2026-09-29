CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c23
DEBUGFLAGS := $(CFLAGS) -g -fanalyzer

.PHONY: clean debug

clean:
	rm -f yabi debug
debug: main.c utils/stack.c
	$(CC) $^ -o $@ $(DEBUGFLAGS)

.DEFAULT_GOAL := yabi
yabi: main.c utils/stack.c
	$(CC) $^ -o $@ $(CFLAGS)
