# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O0 -std=c99 -lm

# Target executable
TARGET = main


# Source files
SRCS = main.c polynomial.c fractal.c format_complex.c write_csv.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

