CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = quest_game

SOURCES = main.cpp Game.cpp Player.cpp Location.cpp Potion.cpp Chest.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe