# Compiler
CXX := g++
# Compiler flags for C++17
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g 
# Include directories
INCLUDE_DIRS := -I. -Ireal_numbers -Ilinear_equations # Added linear_equations

# Source files
SRCS := main.cc \
        real_numbers/real_numbers_utils.cc \
        linear_equations/linear_equations_utils.cc # Added new source

# Object files
OBJS := main.o \
        real_numbers_utils.o \
        linear_equations_utils.o # Added new object

# Executable name
TARGET := math_app # Renamed for general math app

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Built $(TARGET) successfully."

# Rule to compile main.cc
main.o: main.cc real_numbers/real_numbers_utils.h linear_equations/linear_equations_utils.h
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Rule to compile real_numbers_utils.cc
real_numbers_utils.o: real_numbers/real_numbers_utils.cc real_numbers/real_numbers_utils.h real_numbers/real_numbers_types.h
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Rule to compile linear_equations_utils.cc (NEW)
linear_equations_utils.o: linear_equations/linear_equations_utils.cc linear_equations/linear_equations_utils.h linear_equations/linear_equations_types.h
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Target to clean up
clean:
	@echo "Cleaning up..."
	-rm -f $(TARGET) $(OBJS)
	@echo "Clean complete."

# Phony targets
.PHONY: all clean