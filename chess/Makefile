CC = gcc

# Compiler flags
CFLAGS = -I. -I./database -I./moves -I./print -I./chess_art -g 

# Source files
SRCS = chess.c database/database.c moves/moves.c print/print.c chess_art/chess_art.c

# Executable name
EXEC = chess

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