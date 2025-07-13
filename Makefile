# Makefile for MiniShell

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
TARGET = minishell
SOURCES = main.cpp shell.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp shell.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the shell
run: $(TARGET)
	./$(TARGET)

# Debug version
debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)

.PHONY: all clean run debug