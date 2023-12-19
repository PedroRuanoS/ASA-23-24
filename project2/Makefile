# Makefile for compiling the C++ program

# Compiler settings
CXX = g++ 
CXXFLAGS = -std=c++11 -O3 -Wall -lm

# Target binary
TARGET = run

# Source file
SRC = main.cpp

# Default target
all: $(TARGET)

# Rule for building the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean the build
clean:
	rm -f $(TARGET)
