#pragma once
#include "tetromino.hpp"
#include "Well.hpp"
class Painter;
class Game{
        public:
                enum Direction{UP,DOWN,LEFT,RIGHT};
                Game();
                void draw(Painter &);
                void tick();
                void restart();
                void keyEvent(Direction);

        private:
                Well Well_;
                Tetromino tetromino_;
};