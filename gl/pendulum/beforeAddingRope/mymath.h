#ifndef MYMATH_H
#define MYMATH_H
#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#define WIDTH 640
#define HEIGHT 480
#define PI 3.14159265358979323846f
#define dt 0.1f
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
    Circle():m(100.0f){
        s.x=(float)(rand() % WIDTH);
        s.y=(float)(rand() % HEIGHT);
        r  = sqrt(this->m/PI);
        v.x=v.y=5.0f;
        f.x=f.y=0.0f;
        cl.r = (rand() % 256) / 255.0f;
        cl.g = (rand() % 256) / 255.0f;
        cl.b = (rand() % 256) / 255.0f;
    }
    ~Circle(){}
    void draw();
    void update();
    void print();
    //void clearForce(){f.x=0.0f; f.y=0.0f;}
};

#endif // MYMATH_H
