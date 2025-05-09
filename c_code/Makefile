# Compiler
CC := gcc
# Compiler flags for C99/C11, with math library
CFLAGS := -std=c11 -Wall -Wextra -pedantic -g
LDLIBS := -lm # Link math library

# Include directories
INCLUDE_DIRS := -I. -Ireal_numbers -Ilinear_equations # Added linear_equations

# Source files
SRCS := main.c \
        real_numbers/real_numbers_utils.c \
        linear_equations/linear_equations_utils.c # Added new source

# Object files (derive .o names, these will be created in the current directory)
OBJS := $(notdir $(SRCS:.c=.o)) # e.g. main.o, real_numbers_utils.o, linear_equations_utils.o

# Executable name
TARGET := linear_equations_c # Renamed for general math app

# Default target: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
	@echo "Built $(TARGET) successfully."

# Rule to compile main.c into main.o
main.o: main.c real_numbers/real_numbers_utils.h linear_equations/linear_equations_utils.h
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Rule to compile real_numbers/real_numbers_utils.c into real_numbers_utils.o
real_numbers_utils.o: real_numbers/real_numbers_utils.c real_numbers/real_numbers_utils.h real_numbers/real_numbers_types.h
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Rule to compile linear_equations/linear_equations_utils.c into linear_equations_utils.o (NEW)
linear_equations_utils.o: linear_equations/linear_equations_utils.c linear_equations/linear_equations_utils.h linear_equations/linear_equations_types.h
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Target to clean up object files and the executable
clean:
	@echo "Cleaning up..."
	-rm -f $(TARGET) $(OBJS) 
	@echo "Clean complete."

# Phony targets
.PHONY: all clean