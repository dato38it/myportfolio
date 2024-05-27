#pragma once
class Painter;
class Tetromino;
class Well{
        public:
                Well();
                //рисует на рисовальщике Пейнтер
                void draw(Painter &) const;
                //проверка на столкновения тетрамины блоками в колодце
                bool isCollision(const Tetromino &) const;
                //перенос тетромины в колодце
                void unite(const Tetromino &);
		//udalenie zapolnennih strok
                int removeSolidLines();
	private:
                bool map_[20][10];
};
