//#include <iostream>

#include <time.h>
#include <math.h>
#include "mymath.h"
#define N 100

//class Spring{
//public:
//    float k,length;
//    Vec2 fa;//forst from this sping at on other object at end b
//    Circle* a;
//    Circle* b;
//    Spring(){
//        k=0.0f;
//        length=100.0f;
//    }
//    void bind(Circle& _a,Circle& _b){
//        a=&_a; b=&_b;
//    }
//    void update(){
//        Vec2 S = a->s - b->s;//Sab
//        Vec2 So = S.unitVector()*length;//natural position
//        fa=(S - So)*-k;
//        //a->f=a->f + fa;
//        //b->f=b->f - fa;
//    }
//};

Circle balls[N];
//Spring rope;

void collideWall(Circle &A){
    if(A.s.x-A.r<0){
        A.v.x*=-1.0f;
        A.s.x=A.r;
    }
    if(WIDTH<A.s.x+A.r){
        A.v.x*=-1.0f;
        A.s.x=WIDTH-A.r;
    }
    if(A.s.y-A.r<0){
        A.v.y*=-1.0f;
        A.s.y=A.r;
    }
    if(HEIGHT<A.s.y+A.r){
        A.v.y*=-1.0f;
        A.s.y=HEIGHT-A.r;
    }
}
void oneDimension(float &v1,float &v2, float m1,float m2){
    float vtem=v1;
    v1=(vtem*(m1-m2)+2*m2*v2)/(m1+m2);
    v2=(v2*(m2-m1)+2*m1*vtem)/(m1+m2);
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
    //for each ball
//    for(int i=0; i<N; i++) {

//        balls[i].clearForce();
//    }
    //for each rope
    //rope.update();
    //for each pair
    for(int i=0; i<N-1; i++) {
        for(int j=i+1; j<N; j++){
            collideObj(balls[i],balls[j]);
        }
    }
    //for each ball
    for(int i=0; i<N; i++) {
        collideWall(balls[i]);        
        balls[i].update();
        balls[i].draw();
    }
    glFlush();
    glutPostRedisplay();
}

void init(){
    srand((unsigned int)time(NULL));
    //rope.bind(balls[0],balls[1]);
    cout<<WIDTH<<", "<<HEIGHT<<endl;
}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WIDTH,HEIGHT);

    glutCreateWindow("Collision");

    glutDisplayFunc(displayCB);

    glMatrixMode(GL_MODELVIEW);

    init();
    glutMainLoop();
    return 0;
}
