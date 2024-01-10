CXX = g++ 
CXXFLAGS = -std=c++11 -O3 -Wall -lm

TARGET = run

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
