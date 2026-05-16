CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Isrc
LDFLAGS = -lSDL2 -lSDL2_ttf

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
TARGET = bin/hex

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj bin
	@echo "Cleaned up obj/ and bin/ directories."

.PHONY: all clean
