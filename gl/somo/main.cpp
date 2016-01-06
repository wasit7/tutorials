#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846
#define dt 0.1
using namespace std;

struct ball {
    short mass;
    float position[2];
    float velocity[2];
    float color[3];
};

ball Balls[10];
bool once = true;

void drawCircle(float x, float y, float radius) {
    int i;
    int triangleAmount = 20;
    float twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + (radius * cos(i *  twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void moveCircle(ball &ball, short ballNum) {
    for (short m = 0; m < 9; ++m) {
        for (short n = m+1; n < 10; ++n) {
            float distanceBtBalls = sqrt(pow(Balls[m].position[0] - Balls[n].position[0], 2) + pow(Balls[m].position[1] - Balls[n].position[1], 2));
            //cout<<"m,n: "<< m <<"," << n << endl;
            if (distanceBtBalls < Balls[m].mass + Balls[n].mass) {
                float un[2];
                float ut[2];
                un[0] = (Balls[m].position[0] - Balls[n].position[0]) / distanceBtBalls;
                un[1] = (Balls[m].position[1] - Balls[n].position[1]) / distanceBtBalls;
                Balls[m].position[0]+=0.5*un[0]*(
                            Balls[m].mass + Balls[n].mass-distanceBtBalls
                        );
                Balls[m].position[1]+=0.5*un[1]*(
                            Balls[m].mass + Balls[n].mass-distanceBtBalls
                        );
                Balls[n].position[0]-=0.5*un[0]*(
                            Balls[m].mass + Balls[n].mass-distanceBtBalls
                        );
                Balls[n].position[1]-=0.5*un[1]*(
                            Balls[m].mass + Balls[n].mass-distanceBtBalls
                        );
                ut[0] = -un[1]; ut[1] = un[0];

                //cout<<"distanceBtBalls: "<<distanceBtBalls<<endl;
                //cout<<"sqrt(un[0]*un[0]+un[1]*un[1]): "<<sqrt(un[0]*un[0]+un[1]*un[1])<<endl;
                //cout<<"sqrt(ut[0]*ut[0]+ut[1]*ut[1]): "<<sqrt(ut[0]*ut[0]+ut[1]*ut[1])<<endl;
                //cout<<"sqrt(un[0]*ut[0]+un[1]*ut[1]): "<<sqrt(un[0]*ut[0]+un[1]*ut[1])<<endl;
                float v1n = (Balls[m].velocity[0] * un[0]) + (Balls[m].velocity[1] * un[1]);
                float v1t = (Balls[m].velocity[0] * ut[0]) + (Balls[m].velocity[1] * ut[1]);
                float v2n = (Balls[n].velocity[0] * un[0]) + (Balls[n].velocity[1] * un[1]);
                float v2t = (Balls[n].velocity[0] * ut[0]) + (Balls[n].velocity[1] * ut[1]);
                v1n = (v1n * (Balls[m].mass - Balls[n].mass) + (2 * Balls[n].mass * v2n)) / (Balls[m].mass + Balls[n].mass);
                v2n = (v2n * (Balls[n].mass - Balls[m].mass) + (2 * Balls[m].mass * v1n)) / (Balls[m].mass + Balls[n].mass);
                Balls[m].velocity[0] = (v1n * un[0]) + (v1t * ut[0]);
                Balls[m].velocity[1] = (v1n * un[1]) + (v1t * ut[1]);
                Balls[n].velocity[0] = (v2n * un[0]) + (v2t * ut[0]);
                Balls[n].velocity[1] = (v2n * un[1]) + (v2t * ut[1]);
            }
        }
    }
    for (short m = 0; m < 10; ++m) {
        Balls[m].position[0] = Balls[m].position[0] + Balls[m].velocity[0]*dt;
        Balls[m].position[1] = Balls[m].position[1] + Balls[m].velocity[1]*dt;
        if (Balls[m].position[0] - Balls[m].mass <= 0) {
            Balls[m].velocity[0] = abs(Balls[m].velocity[0]);
        }
        else if (Balls[m].position[0] + Balls[m].mass >= 1000){
            Balls[m].velocity[0] = -1.0f*abs(Balls[m].velocity[0]);
        }
        else if (Balls[m].position[1] - Balls[m].mass <= 0){
            Balls[m].velocity[1] = abs(Balls[m].velocity[1]);
        }
        else if (Balls[m].position[1] + Balls[m].mass >= 600) {
            Balls[m].velocity[1] = -1.0f*abs(Balls[m].velocity[1]);
        }
    }
}

void renderScene() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 600.0, 0.0);

    srand(time(NULL));
    if (once == true) {
        for (short i = 0; i < 10; ++i) {
            Balls[i].mass = rand() % 31 + 10;
            Balls[i].position[0] = rand() % (501 - Balls[i].mass);
            Balls[i].position[1] = rand() % (501 - Balls[i].mass);
            short random = rand() % 2;
            Balls[i].velocity[0] = ((rand() % 11) + 1) / 10.0f;
            Balls[i].velocity[1] = ((rand() % 11) + 1) / 10.0f;
            Balls[i].color[0] = (rand() % 256) / 255.0f;
            Balls[i].color[1] = (rand() % 256) / 255.0f;
            Balls[i].color[2] = (rand() % 256) / 255.0f;
        }
        once = false;
    }
    for (short i = 0; i < 10; ++i) {
        glColor3f(Balls[i].color[0], Balls[i].color[1], Balls[i].color[2]);
        moveCircle(Balls[i], i);
        drawCircle(Balls[i].position[0], Balls[i].position[1], Balls[i].mass);
        if(i==0)
            cout << "Ball" << i << " Mass:" << Balls[i].mass << " Position: " << Balls[i].position[0] << ", " << Balls[i].position[1] << " Velocity: " << Balls[i].velocity[0] << ", " << Balls[i].velocity[1] << endl;
    }
    glFlush();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Collision");
    glutDisplayFunc(renderScene);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 0;
}
