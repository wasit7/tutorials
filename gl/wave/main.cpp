#include <time.h>
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#define N 10 //number of balls
#define WIDTH 1280
#define HEIGHT 700
#define PI 3.14159265358979323846f
#include "mymath.h"
Circle balls[N];
void displayCB(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);
    //glutSwapBuffers();
}

void init(){
    balls[0].setStatic();
    for
}
void mainUpdate(){
    //for each ball
    for(int i=0; i<N; i++) {
        balls[i].f.x=0;
    }





    //for each ball
    for(int i=0;i<N;i++){
        balls[i].draw();
    }
    glFlush();
    glutPostRedisplay();
}

void idleCB(){
    static GLuint start=0,stop=0,now=0,interval=1;
    static char window_title[20];
    start=stop;
    stop=start+(GLuint)(1000.0f*dt);
    mainUpdate();
    while(now<stop){
        now=glutGet(GLUT_ELAPSED_TIME);
        interval=now-start;
    }
    sprintf(window_title, "fps: %3.1f, time: %dms", 1000.0f/(float)interval,interval);
    glutSetWindowTitle(window_title);
    stop=glutGet(GLUT_ELAPSED_TIME);
}
void MouseCB(int x, int y){
    balls[0].s.x=x;
    balls[0].s.y=y;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glutCreateWindow("...");
    glutDisplayFunc(displayCB);
    glutIdleFunc(idleCB);
    glutMotionFunc(MouseCB);

    init();
    glutMainLoop();
    return 0;
}
