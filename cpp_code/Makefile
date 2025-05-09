# Compiler
CXX := g++
# Compiler flags for C++17
CXXFLAGS := -std=c++17 -Wall -Wextra -Wno-unused-parameter -pedantic -g
# Include directories: current, and the 'three_d_geometry' subdirectory
INCLUDE_DIRS := -I. -Ithree_d_geometry

# Source files
SRCS := main.cc three_d_geometry/three_d_utils.cc

# Object files (will be created in the current directory)
OBJS := main.o three_d_utils.o

# Executable name
TARGET := 3d_geometry_app_cpp

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Built $(TARGET) successfully."

# Rule to compile main.cc
main.o: main.cc three_d_geometry/three_d_utils.h three_d_geometry/three_d_types.h
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Rule to compile three_d_utils.cc
three_d_utils.o: three_d_geometry/three_d_utils.cc three_d_geometry/three_d_utils.h three_d_geometry/three_d_types.h
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Target to clean up
clean:
	@echo "Cleaning up..."
	-rm -f $(TARGET) $(OBJS)
	@echo "Clean complete."

# Phony targets
.PHONY: all clean