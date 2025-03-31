# Makefile for ECE013 - Lab06
#
# @file		GNUmakefile
#
# @date		23 Oct 2024

# NOTE: You must edit this path to point to your common directory!
include_dir = ../Common

## Compiler.
CC := gcc

## Flags.
# CFLAGS	Compiler flags.
CFLAGS := -Wall -std=c11
# CPPFLAGS	Preprocessor flags.
CPPFLAGS := -I$(include_dir) -Iinclude

# Source and object files.
DEFAULT_SRCS := src/Lab06_main.c src/sort.c src/LinkedList.c src/stopwatch.c
DEFAULT_OBJS := $(DEFAULT_SRCS:.c=.o)

LLTEST_SRCS := src/LinkedListTest.c src/LinkedList.c $(include_dir)/BOARD.c
LLTEST_OBJS := $(LLTEST_SRCS:.c=.o)

# Executable/Target.
TARGET := Lab06

# Default.
all: $(TARGET)

# Rule to create default executable.
$(TARGET): $(DEFAULT_OBJS)
	@echo "Building Lab06..."
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFAULT_SRCS) -o $@
	@echo "DONE."

# NOTE: Run `$ make LinkedListTest` to build the LinkedListTest.c test harness.
LinkedListTest: $(LLTEST_OBJS)
	@echo "Building LinkedListTest test harness..."
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LLTEST_SRCS) -o $@
	@echo "DONE."

clean:
	@echo "Tidying up..."
	rm -f $(DEFAULT_OBJS) $(LLTEST_OBJS) $(TARGET) LinkedListTest
	@echo "DONE."

.PHONY: all clean
