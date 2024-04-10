CPPFLAGS=-Wall -g
OBJECTS=tetris.o painter.o tetromino.o well.o game.o
%.0: %.cpp
    g++ -c $(CPPFLAGS) -o $@ $<
tetris: $(OBJECTS)
    g++ $(OBJECTS) -o tetris -g -lglut
tetris.o: tetris.cpp game.hpp well.hpp painter.hpp tetromino.hpp
painter.o: painter.cpp painter.hpp
tetromino.o: tetromino.cpp tetromino.hpp painter.hpp
well.o: well.cpp well.hpp tetromino.hpp painter.hpp
game.o: game.cpp game.hpp well.hpp tetromino.hpp painter.hpp