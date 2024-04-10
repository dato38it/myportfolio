#include "painter.hpp"
#include "tetromino.hpp"
#include "well.hpp"
#include <GL/glut.h>
void display(){
        glClear(GL_COLOR_BUFFER_BIT);
        Painter p;
        Well w;
    Tetromino t(Tetromino::T);
        Tetromino t1=t;
        Tetromino t2=t;
        Tetromino t3=t;
        t1.move(0,4);
        t1.rotate(Tetromino::LEFT);
        t2.move(0,8);
        t2.rotate(Tetromino::LEFT);
        t2.rotate(Tetromino::LEFT);
        t3.move(0,12);
        t3.rotate(Tetromino::LEFT);
        t3.rotate(Tetromino::LEFT);
        t3.rotate(Tetromino::LEFT);
    w.unite(t3);
        w.draw(p);
    t.draw(p);
    t1.draw(p);
        t2.draw(p);
    glutSwapBuffers();
}
int main(int argc, char **argv){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(10*8, 20*8);//10x20 Razmer kolodca
        glutInitWindowPosition(100,780);
        glutCreateWindow("Tetris");
        glClearColor(0,0,0,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 10*8, 20*8, 0, -1.0, 1.0);
        glutDisplayFunc(display);
        glutMainLoop();
}