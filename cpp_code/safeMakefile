# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. # Use C++17 for std::optional, -I. to find lines/ dir
LDFLAGS =

# Source files
SRCS = main.cc lines/slope.cc
# Object files (derived from source files)
OBJS = $(SRCS:.cc=.o)

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
# This generic rule handles both main.cc and lines/slope.cc
%.o: %.cc lines/slope.h lines/geometry_types.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cc specifically (alternative if generic rule has issues)
# main.o: main.cc lines/slope.h lines/geometry_types.h
#	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

# Compile lines/slope.cc specifically (alternative)
# lines/slope.o: lines/slope.cc lines/slope.h lines/geometry_types.h
#	$(CXX) $(CXXFLAGS) -c lines/slope.cc -o lines/slope.o

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean













# CC = g++
# CFLAGS = -Wall -std=c++11

# all: main

# main: main.cc lines/slope.cc
# 	$(CC) $(CFLAGS) main.cc lines/slope.cc -o main

# clean:
# 	rm -f main
