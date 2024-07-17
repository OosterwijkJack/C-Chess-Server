# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iserver -Itools -g -Ichess -Ichess/chess_art -Ichess/database -Ichess/logic -Ichess/moves -Ichess/print 

# Source files
SRCS = main.c server/client.c server/server.c tools/tools.c chess/chess.c chess/chess_art/chess_art.c chess/database/database.c chess/logic/logic.c chess/moves/moves.c chess/print/print.c

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