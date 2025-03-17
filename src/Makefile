# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

# Output executable name
TARGET = HW9

# Source files for Dijkstra
SRC = dijkstras_main.cpp dijkstras.cpp
OBJ = $(SRC:.cpp=.o)

# Default rule: Compile the program
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile .cpp files into .o files
%.o: %.cpp dijkstras.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)
