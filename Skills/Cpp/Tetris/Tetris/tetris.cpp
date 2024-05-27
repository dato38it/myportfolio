#include "painter.hpp"
#include <GL/glut.h>
void display(){
        glClear(GL_COLOR_BUFFER_BIT);
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