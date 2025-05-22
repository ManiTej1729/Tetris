# Makefile for Tetris game

# Compiler and flags
CC = gcc
CFLAGS = -lncurses -lpthread
SRC = main.c tetris.c
TARGET = tetris

# Default target: compile and run
all: $(TARGET)
	./$(TARGET)

# Compile the tetris game
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

# Target for running with delay parameter
delay:
	@if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "Usage: make delay VALUE"; \
	else \
		$(MAKE) $(TARGET); \
		./$(TARGET) $(filter-out $@,$(MAKECMDGOALS)); \
	fi

# Catch non-targets so they don't cause errors
%:
	@:

# Clean up compiled files
clean:
	rm -f $(TARGET)

.PHONY: all delay clean
