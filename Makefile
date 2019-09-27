CC = gcc
OPTIMIZATION-OPTION = -O3
BASIC-OPTIONS = -std=c99 -lm -O3 -o
DEPENDS = perfect-number-tester.c perfect-numbers.c perfect-numbers.h
FILES = perfect-number-tester.c perfect-numbers.c
OUT_EXEC = perfect-number

build: $(DEPENDS)
	$(CC) $(BASIC-OPTIONS) $(OUT_EXEC) $(FILES)

clean:
	rm -f $(OUT_EXEC) core

rebuild: clean build

run:
	./$(OUT_EXEC)

build-run: build run