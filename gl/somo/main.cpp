#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846f
#define dt 0.1f
#define N 200
#define WIDTH 1000
#define HEIGHT 600
using namespace std;

class myObj{
public:
    float m,r,sx,sy,vx,vy,cr,cg,cb;
    myObj(){
        this->m  = float(rand() % 500 + 100);
        this->r  = sqrt(this->m/PI);
        this->sx = float(rand() % WIDTH);
        this->sy = float(rand() % HEIGHT);
        this->vx = ((rand() % 100) - 50) / 10.0f;
        this->vy = ((rand() % 100) - 50) / 10.0f;
        this->cr = (rand() % 256) / 255.0f;
        this->cg = (rand() % 256) / 255.0f;
        this->cb = (rand() % 256) / 255.0f;
    }
    ~myObj(){
        cout<<"deconstruct m:"<<this->m<<endl;
    }
    void draw();
    void update();
    void update(float sx, float sy, float vx, float vy);
    void print();
};
myObj balls[N];
void myObj::draw(){
    int triangleAmount = 20;
    float twicePi = 2.0f * PI;
    glColor3f(this->cr,this->cg,this->cb);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(this->sx, this->sy);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            this->sx + (this->r * cos(i * twicePi / triangleAmount)),
            this->sy + (this->r * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}
void myObj::update(void){
    this->sx+=dt*this->vx;
    this->sy+=dt*this->vy;
}
void myObj::update(float sx, float sy, float vx, float vy){
    cout<<"debug: update(sx,sy,vx,vy)"<<endl;
}
void myObj::print(){
    cout<<"m:"<<this->m<<" r:"<<this->r
        <<" sx:"<<this->sx<<" sy:"<<this->sy
        <<" vx:"<<this->vx<<" vy:"<<this->vy
        //<<" cr:"<<this->cr<<" cg:"<<this->cg<<" cb:"<<this->cb
        <<endl;
}
void init(){
    srand((unsigned int)time(NULL));
}
void collideWall(myObj &A){
    if(A.sx-A.r<0){
        A.vx*=-1.0f;
        A.sx=A.r;
    }
    if(WIDTH<A.sx+A.r){
        A.vx*=-1.0f;
        A.sx=WIDTH-A.r;
    }
    if(A.sy-A.r<0){
        A.vy*=-1.0f;
        A.sy=A.r;
    }
    if(HEIGHT<A.sy+A.r){
        A.vy*=-1.0f;
        A.sy=HEIGHT-A.r;
    }
}
void oneDimension(float &v1,float &v2, float m1,float m2){
    float vtem=v1;
    v1=(vtem*(m1-m2)+2*m2*v2)/(m1+m2);
    v2=(v2*(m2-m1)+2*m1*vtem)/(m1+m2);
}
class vec2{
public:
    float x,y;
    vec2(float x, float y){
        this->x=x;
        this->y=y;
    }
    float magnitude(){
        return sqrt(this->x*this->x + this->y*this->y);
    }
};

void collideObj(myObj &A, myObj &B){
    vec2 en=vec2(B.sx-A.sx, B.sy-A.sy);//vector between A to B
    float mag=en.magnitude();
    en.x/=mag;
    en.y/=mag;
    vec2 et=vec2(-en.y,en.x);
    //cout<<"Debug "<<et.magnitude()<<", "<<et.magnitude()<<endl;
    //en=[nx,ny] and et=[tx,ty] are now unit vectors
    //for normal and tangent directions
    if(mag < A.r+B.r){
        B.sx+= (A.r+B.r-mag)*en.x;
        A.sx-= (A.r+B.r-mag)*en.x;
        B.sy+= (A.r+B.r-mag)*en.y;
        A.sy-= (A.r+B.r-mag)*en.y;
        float vnA=A.vx*en.x + A.vy*en.y;
        float vtA=A.vx*et.x + A.vy*et.y;
        float vnB=B.vx*en.x + B.vy*en.y;
        float vtB=B.vx*et.x + B.vy*et.y;
        oneDimension(vnA,vnB,A.m,B.m);
        A.vx=vnA*en.x+vtA*et.x;
        A.vy=vnA*en.y+vtA*et.y;
        B.vx=vnB*en.x+vtB*et.x;
        B.vy=vnB*en.y+vtB*et.y;
    }
}

void displayCB(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 600.0, 0.0);
    for(int i=0; i<N-1; i++) {
        for(int j=i+1; j<N; j++){
            collideObj(balls[i],balls[j]);
        }
    }
    for(int i=0; i<N; i++) {
        collideWall(balls[i]);
        balls[i].update();
        balls[i].draw();
        //balls[i].print();
    }
    glFlush();
    glutPostRedisplay();
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
