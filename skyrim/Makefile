CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O3
TARGET = parser
SRC = parser.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
