CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SRCS = src/main.c src/lexer.c src/ast.c src/parser.c
TARGET = hlxc

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "✓ hlxc compiler built successfully!"

clean:
	rm -f $(TARGET)

test: all
	./hlxc ../examples/basic/hello.hlx

.PHONY: all clean test
