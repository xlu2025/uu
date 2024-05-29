XX = g++
CXXFLAGS = -I../include -g -O0 -std=c++11 -lncurses
TARGET = air_hockey
OBJECTS = air_hockey.o ball.o slider.o zone.o key.o obstacle.o
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
