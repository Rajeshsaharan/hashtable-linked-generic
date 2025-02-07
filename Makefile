# Makefile for C Project with Multiple Source Files

# Compiler
CC = gcc

# Compiler flags
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -std=c11: Use C11 standard
# -g: Add debugging information
CFLAGS = -Wall -Wextra -std=c11 -g

# Linker flags (if needed)
LDFLAGS = 

# Target executable name
TARGET = main

# Source files
SRCS = main.c linked_list.c hashtable.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files (for dependency tracking)
HEADERS = linked_list.h hashtable.h

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (targets that don't represent files)
.PHONY: all clean

# Specific dependencies
main.o: main.c linked_list.h hashtable.h
linked_list.o: linked_list.c linked_list.h
hashtable.o: hashtable.c hashtable.h