CXX      = g++
CXXFLAGS = -Wall
CXXLIBS  = -lncurses
DEPS     = Cell.h Maze.h debug.h Player.h Emezama.h Window.h Stack.h SearchingAlgorithms.h makefile
OBJS     = main.o Maze.o Cell.o Player.o Emezama.o Window.o SearchingAlgorithms.o
PROGNAME = Emezama

all: $(PROGNAME)

debug: CXXFLAGS += -g -D_DEBUG 
debug: $(PROGNAME)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROGNAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o $@ $^

clean:
	rm -f $(PROGNAME) $(OBJS)
