#include <stdio.h>
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
//#include "SOIL.H"
//#include "device.h"

//#include <cutil_inline.h>
//#include <cutil_gl_inline.h>

#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
unsigned int width=640;
unsigned int height=480;
GLuint gl_tex;
void displayCB();
void mouseCB(int button, int state, int x, int y);
void mouseMotionCB(int x, int y);
void reshapeCB(int w, int h);
//view parameter
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;

int main(int argc, char **argv){
    // Initialize OpenGL and GLUT for device 0
    // and make the OpenGL context current
    printf("debug00:\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(512,512);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(displayCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutReshapeFunc(reshapeCB);
    glEnable(GL_TEXTURE_2D);

    //gen gl_tex
    glGenTextures(1, &gl_tex);
    //bind gl_tex
    glBindTexture(GL_TEXTURE_2D, gl_tex);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, h_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    //update gl_tex
    float pixels[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    glBindTexture(GL_TEXTURE_2D, gl_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    //main loop
    glutMainLoop();
}
void displayCB(){
    // tramsform camera
    glClearColor(0.5f,0.5f,0.5f,0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,1,0,0,0,0,1,0);
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading



    //render
    /*
    float pixels[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    glBindTexture(GL_TEXTURE_2D, gl_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
    */
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    //glColor4f(0.5, 0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 1.0f);
    glEnd();
    //glBindTexture(GL_TEXTURE_2D, 0);


    glutSwapBuffers();
    glutPostRedisplay();
}
void mouseCB(int button, int state, int x, int y){
    mouseX = (float)x;
    mouseY = (float)y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}
void mouseMotionCB(int x, int y){
    if(mouseLeftDown)
    {
        cameraAngleY += 0.2f*(x - mouseX);
        cameraAngleX += 0.2f*(y - mouseY);
        mouseX = (float)x;
        mouseY = (float)y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.1f;
        mouseY = (float)y;
    }
    //printf("cameraDistance %f%\n",cameraDistance);
    glutPostRedisplay();
}
void reshapeCB(int w, int h){
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // set perspective viewing frustum
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
   gluPerspective(36.0f, (float)(w)/h, 0.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}
