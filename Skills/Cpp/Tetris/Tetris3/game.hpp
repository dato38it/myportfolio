#pragma once
class Game{
        public:
                enum Direction{UP,DOWN,LEFT,RIGHT};
                void draw(Painter &);
                void tick();
                void restart();
                void keyEvent(Direction);
};