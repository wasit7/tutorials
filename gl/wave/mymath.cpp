#include "mymath.h"

Vec2::Vec2(float _x, float _y):x(_x),y(_y){}
float Vec2::magnitude(){
    return sqrt(x*x + y*y);
}
Vec2 Vec2::unitVector(){
    Vec2 temp;
    float mag=this->magnitude();
    temp.x=this->x/mag;
    temp.y=this->y/mag;
    return temp;
}
Vec2 Vec2::operator*(float c){//postfix only
    Vec2 temp;
    temp.x=x*c;
    temp.y=y*c;
    return temp;
}
Vec2 Vec2::operator/(float c){//postfix only
    Vec2 temp;
    temp.x=x/c;
    temp.y=y/c;
    return temp;
}
Vec2 Vec2::operator+(Vec2 B){
    Vec2 temp;
    temp.x=x+B.x;
    temp.y=y+B.y;
    return temp;
}
Vec2 Vec2::operator-(Vec2 B){
    Vec2 temp;
    temp.x=x-B.x;
    temp.y=y-B.y;
    return temp;
}
Vec2 Vec2::operator=(Vec2 B){
    x=B.x;
    y=B.y;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vec2& A) {
    return out << "\t"<<A.x << ", "<< A.y << "\n";
}

#define NTriangle 36
void Circle::draw(){
    float twicePi = 2.0f * PI;
    glColor3f(cl.r,cl.g,cl.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(s.x, s.y);
    for (int i = 0; i <= NTriangle; i++) {
        glVertex2f(
            s.x + (r * cos(i * twicePi / NTriangle)),
            s.y + (r * sin(i * twicePi / NTriangle))
        );
    }
    glEnd();
}
void Circle::update(void){
    if (isMovable){
        v=v+f/m*dt;
        s=s+(v*dt);
    }else{
        v.x=0.0f;
        v.y=0.0f;
    }
    //cout<<"Debug: Circle:update s"<<s<<

    //s.x+=v.x*dt;
    //s.y+=v.y*dt;
}
void Circle::print(){
    cout<<"m:"<<m<<" r:"<<r
        <<" sx:"<<s.x<<" sy:"<<s.y
        <<" vx:"<<v.x<<" vy:"<<v.y
        <<endl;
}
