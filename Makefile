# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iserver -Itools -g 

# Source files
SRCS = main.c server/client.c server/server.c tools/tools.c

# Executable name
EXEC = main

# Default rule
all:
	$(EXEC)

# Rule to compile source files directly into the executable
$(EXEC):
	$(CC) $(CFLAGS) $(SRCS) -o $@

# Clean rule to remove the generated executable
clean:
	rm -f $(EXEC)

# Phony targets to avoid conflict with files of the same name
.PHONY: all clean