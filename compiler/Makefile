CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -D_POSIX_C_SOURCE=200809L
SRCS = src/main.c src/lexer.c src/ast.c src/parser.c src/semantic.c src/interpreter.c
TARGET = hlxc

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "✓ hlxc compiler built!"

clean:
	rm -f $(TARGET)

test: all
	./hlxc run ../examples/basic/hello.hlx

.PHONY: all clean test
