#ifndef MYMATH_H
#define MYMATH_H
#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#define WIDTH 1280
#define HEIGHT 700
#define PI 3.14159265358979323846f
#define dt 0.004f

using namespace std;
struct Color{
    float r;
    float g;
    float b;
};

class Vec2{
public:
    float x,y;
    Vec2(){}
    Vec2(float _x, float _y);
    float magnitude();
    Vec2 unitVector();
    Vec2 operator+(Vec2 B);
    Vec2 operator-(Vec2 B);
    Vec2 operator=(Vec2 B);
    Vec2 operator*(float c);
    Vec2 operator/(float c);
    friend std::ostream& operator<<(std::ostream&, const Vec2&);
};

class Circle{
public:
    float m,r;
    Vec2 s,v,f;
    Color cl;
    bool isMovable;
    Circle():m(10.0f){
        isMovable=1;
        s.x=0.9f*WIDTH+ (float)(rand() % 256)/256.0f;
        s.y=0.1f*HEIGHT+(float)(rand() % 256)/256.0f;
        r  = sqrt(this->m/PI*25);
        v.x=v.y=0.0f;
        f.x=f.y=0.0f;
        cl.r = (rand() % 256) / 255.0f;
        cl.g = (rand() % 256) / 255.0f;
        cl.b = (rand() % 256) / 255.0f;
    }
    ~Circle(){}
    void draw();
    void update();
    void print();
    void clearForce(){f.x=0.0f; f.y=0.0f;}
    void setStatic(){isMovable=0;cl.r=0;cl.g=0;cl.b=0;}
};

#endif // MYMATH_H
