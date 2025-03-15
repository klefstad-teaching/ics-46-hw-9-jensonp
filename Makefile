CXX      = g++
CXXFLAGS := -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -fsanitize=address,undefined 

SRCDIR  = src

DIJKSTRA_SRCS = $(SRCDIR)/dijkstras.cpp $(SRCDIR)/dijkstras_main.cpp
DIJKSTRA_OBJS = $(DIJKSTRA_SRCS:.cpp=.o)
DIJKSTRA_TARGET = dijkstras

LADDER_SRCS = $(SRCDIR)/ladder.cpp $(SRCDIR)/ladder_main.cpp
LADDER_OBJS = $(LADDER_SRCS:.cpp=.o)
LADDER_TARGET = ladder

all: $(DIJKSTRA_TARGET) $(LADDER_TARGET)

$(DIJKSTRA_TARGET): $(DIJKSTRA_OBJS)
	$(CXX) $(CXXFLAGS) -o $(DIJKSTRA_TARGET) $(DIJKSTRA_OBJS)

$(LADDER_TARGET): $(LADDER_OBJS)
	$(CXX) $(CXXFLAGS) -o $(LADDER_TARGET) $(LADDER_OBJS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(DIJKSTRA_OBJS) $(LADDER_OBJS) $(DIJKSTRA_TARGET) $(LADDER_TARGET)
