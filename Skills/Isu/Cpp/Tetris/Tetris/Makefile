CPPFLAGS=-Wall -g
OBJECTS=tetris.o painter.o
%.0: %.cpp
        g++ -c $(CPPFLAGS) -o $@ $<
tetris: $(OBJECTS)
        g++ $(OBJECTS) -o tetris -g -lglut
tetris.o: tetris.cpp painter.hpp
painter.o: painter.cpp painter.hpp