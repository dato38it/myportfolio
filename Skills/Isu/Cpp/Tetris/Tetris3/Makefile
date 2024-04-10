CPPFLAGS=-Wall -g
OBJECTS=tetris.o painter.o tetromino.o
%.0: %.cpp
    g++ -c $(CPPFLAGS) -o $@ $<
tetris: $(OBJECTS)
    g++ $(OBJECTS) -o tetris -g -lglut
tetris.o: tetris.cpp painter.hpp tetromino.hpp
painter.o: painter.cpp painter.hpp
tetromino.o: tetromino.cpp tetromino.hpp painter.hpp