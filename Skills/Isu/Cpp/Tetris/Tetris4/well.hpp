#pragma once
class Well{
        public:
                Well();
                //рисует на рисовальщике Пейнтер
                void draw(Painter &) const;
                //проверка на столкновения тетрамины блоками в колодце
                bool isCollision(const Tetromino &) const;
                //перенос тетромины в колодце
                void unite(const Tetromino &);
};