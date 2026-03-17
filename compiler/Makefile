CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -D_POSIX_C_SOURCE=200809L
SRCS = src/main.c src/lexer.c src/ast.c src/parser.c src/semantic.c src/interpreter.c src/codegen.c
TARGET = hlxc

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) -lm
	@echo "✓ hlxc compiler built!"

clean:
	rm -f $(TARGET)

test: all
	./hlxc run ../tests/final_test.hlx

.PHONY: all clean test
