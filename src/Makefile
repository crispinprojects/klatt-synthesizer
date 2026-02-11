# =====================================================================================
# Makefile for Klatt Speech Synthesizer
# Last Updated: Monday, February 02, 2026
# =====================================================================================

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I.
LDFLAGS = -lm

# Executable name
TARGET = synthesizer

# Source files
SRCS = main.c synthesizer.c phonemes.c

# Object files
OBJS = $(SRCS:.c=.o)

# The default target.
# This will build the executable.
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile each C source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the generated files
clean:
	rm -f $(TARGET) $(OBJS) *.wav
