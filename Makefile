CXX = g++
CXXFLAGS = -Wall -Wextra -fsanitize=address -I./include
SRCS = main.cpp Microplot.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = microplot

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
