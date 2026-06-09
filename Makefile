CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SOURCES = main.cpp Game.cpp Player.cpp Location.cpp Potion.cpp Chest.cpp
OBJECTS = $(SOURCES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET = quest_game.exe
	RM = del /Q
else
	TARGET = quest_game
	RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)