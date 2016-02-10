//#include <iostream>

#include <time.h>
#include <math.h>
#include "mymath.h"
#include <stdio.h>
#define N 100 //number of balls
#define M 100     //number of ropes
#define SpringLenght 1.0f
#define G 980.0f //pixles per second square
#define LAMBDA 0.8f
class Spring{
public:
    float k,length;
    Vec2 fa;//forst from this sping at on other object at end b
    Circle* a;
    Circle* b;
    bool isBind;
    Spring(){
        isBind=0;
        k=1000.0f;
        length=SpringLenght;
    }
    void bind(Circle& _a,Circle& _b){
        a=&_a; b=&_b;
        isBind=1;
    }
    void update(){
        if(isBind){
            Vec2 S = a->s - b->s;//Sab
            Vec2 So = S.unitVector()*length;//natural position
            if(length<S.magnitude()){
                fa=(S - So)*-k;
            }else{
                fa.x=0.0f;
                fa.y=0.0f;
            }
            a->f=a->f + fa;
            b->f=b->f - fa;

            //energy lost
            if(a->isMovable){
                a->s=a->s-S*0.001f;
            }
            if(b->isMovable){
                b->s=b->s+S*0.001f;
            }
        }
    }
    void draw(){
        if(isBind){
            glColor3f(0,0,0);
            glBegin(GL_LINES);
            glVertex2d(a->s.x,a->s.y);
            glVertex2d(b->s.x,b->s.y);
            glEnd();
        }
    }
    void print(){
        cout<<"Debug:Spring fa"<<fa;
        cout<<"Debug:Spring sa"<<a->s;
        cout<<"Debug:Spring sb"<<b->s;
    }
};

Circle balls[N];
Spring rope[M];

void collideWall(Circle &A){
    if(A.s.x-A.r<0){
        A.v.x*=-LAMBDA;
        A.s.x=A.r;
    }
    if(WIDTH<A.s.x+A.r){
        A.v.x*=-LAMBDA;
        A.s.x=WIDTH-A.r;
    }
    if(A.s.y-A.r<0){
        A.v.y*=-LAMBDA;
        A.s.y=A.r;
    }
    if(HEIGHT<A.s.y+A.r){
        A.v.y*=-LAMBDA;
        A.s.y=HEIGHT-A.r;
    }
}
void oneDimension(float &v1,float &v2, float m1,float m2){
    float vtem=v1;
    v1=LAMBDA*(vtem*(m1-m2)+2*m2*v2)/(m1+m2);
    v2=LAMBDA*(v2*(m2-m1)+2*m1*vtem)/(m1+m2);
}


void collideObj(Circle &A, Circle &B){
    Vec2 en=Vec2(B.s.x-A.s.x, B.s.y-A.s.y);//vector between A to B
    float mag=en.magnitude();
    en.x/=mag;
    en.y/=mag;
    Vec2 et=Vec2(-en.y,en.x);
    //cout<<"Debug "<<et.magnitude()<<", "<<et.magnitude()<<endl;
    //en=[nx,ny] and et=[tx,ty] are now unit vectors
    //for normal and tangent directions
    if(mag < A.r+B.r){
        B.s.x+= (A.r+B.r-mag)*en.x;
        A.s.x-= (A.r+B.r-mag)*en.x;
        B.s.y+= (A.r+B.r-mag)*en.y;
        A.s.y-= (A.r+B.r-mag)*en.y;
        float vnA=A.v.x*en.x + A.v.y*en.y;
        float vtA=A.v.x*et.x + A.v.y*et.y;
        float vnB=B.v.x*en.x + B.v.y*en.y;
        float vtB=B.v.x*et.x + B.v.y*et.y;
        oneDimension(vnA,vnB,A.m,B.m);
        A.v.x=vnA*en.x+vtA*et.x;
        A.v.y=vnA*en.y+vtA*et.y;
        B.v.x=vnB*en.x+vtB*et.x;
        B.v.y=vnB*en.y+vtB*et.y;
    }
}

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
    //balls[M-1].setStatic();
    balls[0].s.x=WIDTH*0.5;
    balls[0].s.y=0;

    srand((unsigned int)time(NULL));
    float theta =10.0f/180.0f*PI;
    balls[1].s.x=WIDTH*0.5+SpringLenght*sin(theta);
    balls[1].s.y=0+SpringLenght*cos(theta);

    for(int i=0;i<N-1;i++){
        rope[i].bind(balls[i],balls[i+1]);
    }

}
void mainUpdate(){
    //for each ball
    for(int i=0; i<N; i++) {
        balls[i].f.x=0;
        balls[i].f.y=G*balls[i].m;
        //balls[i].f.y=0;
    }
    //for each rope
    for(int i=0;i<M;i++){
        rope[i].update();
    }

    //for each pair of balls check collision
    for(int i=0; i<N-1; i++) {
        for(int j=i+1; j<N; j++){
            collideObj(balls[i],balls[j]);
        }
    }

    for(int i=0; i<N; i++) {
        collideWall(balls[i]);
        balls[i].update();
        balls[i].draw();
    }
    //for each ball
    for(int i=0;i<M;i++){
        rope[i].draw();
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
