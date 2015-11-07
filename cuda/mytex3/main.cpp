#include <stdio.h>
#include <stdexcept>
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

//#include "SOIL.H"
#include "device.h"

//#include <cutil_inline.h>
//#include <cutil_gl_inline.h>

//#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
const dim3 windowSize(512, 512);
GLuint pbo;         // OpenGL pixel buffer object
uchar4 *d_output = NULL;
uchar4 *h_output = NULL;
struct cudaGraphicsResource *cuda_pbo_resource = NULL; // CUDA Graphics Resource (to transfer PBO)
void idleCB();
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

extern "C"
void device_render(uchar4 *d_output, uint width, uint height);
void checkCudaErrors(cudaError_t e){
    if (e) throw std::runtime_error(cudaGetErrorString(e));
}
void reshape(int x, int y)
{
    glViewport(0, 0, x, y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
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
void initGL(int *argc, char **argv){
    // initialize GLUT callback functions
    glutInit(argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowSize.x, windowSize.y);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(displayCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutReshapeFunc(reshape);
    glutIdleFunc(idleCB);

    glewInit();

    if (!glewIsSupported("GL_VERSION_2_0 GL_ARB_pixel_buffer_object"))
    {
        fprintf(stderr, "Required OpenGL extensions missing.");
        exit(EXIT_FAILURE);
    }
}
void initGLBuffers(){
    // create pixel buffer object
    glGenBuffersARB(1, &pbo);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo);
    glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, windowSize.x*windowSize.y*sizeof(GLubyte)*4, 0, GL_STREAM_DRAW_ARB);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

    // register this buffer object with CUDA
    checkCudaErrors(cudaGraphicsGLRegisterBuffer(&cuda_pbo_resource, pbo, cudaGraphicsMapFlagsWriteDiscard));
}

void render(){
    // map PBO to get CUDA device pointer
    static uint i=0;
    checkCudaErrors(cudaGraphicsMapResources(1, &cuda_pbo_resource, 0));
    size_t num_bytes;


    checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void **)&d_output, &num_bytes, cuda_pbo_resource));
    h_output=(uchar4*)malloc(num_bytes);
    // call CUDA kernel, writing results to PBO
    //renderAtlasImage(windowGridSize, windowBlockSize, d_output, windowSize.x, windowSize.y, lod);
    device_render(d_output,windowSize.x,windowSize.y);

    checkCudaErrors(cudaGraphicsUnmapResources(1, &cuda_pbo_resource, 0));

    cudaMemcpy(h_output,d_output,num_bytes,cudaMemcpyDeviceToHost);
    printf("h_output[%d]:%d %d %d %d\n",i,h_output[i].x,h_output[i].y,h_output[i].z,h_output[i].w);
    //i++;
}

// display results using OpenGL (called by GLUT)
void displayCB()
{
    static uint ti=glutGet(GLUT_ELAPSED_TIME);
    static uint nf=0;
    render();

    // display results
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.5f,0.5f,0.5f,0.5f);
    // draw image from PBO

    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(0, 0);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo);
    glDrawPixels(windowSize.x, windowSize.y, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

    glutSwapBuffers();
    glutReportErrors();

    if(1e3<(glutGet(GLUT_ELAPSED_TIME)-ti)){
        char fps[256];
        sprintf_s(fps, "%3d fps", nf);
        glutSetWindowTitle(fps);
        ti=glutGet(GLUT_ELAPSED_TIME);
        nf=0;
    }else nf++;
}
void idleCB(){
    glutPostRedisplay();
}

int main(int argc, char **argv){
    // Initialize OpenGL and GLUT for device 0
    // and make the OpenGL context current
    cudaDeviceReset();
    initGL(&argc,argv);
    cudaGLSetGLDevice(0);
    cudaSetDevice(0);
    initGLBuffers();
//    glEnable(GL_TEXTURE_2D);
    glutMainLoop();
}
//void displayCB2(){


//    // tramsform camera
//    glClearColor(0.5f,0.5f,0.5f,0.5f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0,0,1,0,0,0,0,1,0);
//    glTranslatef(0, 0, cameraDistance);
//    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
//    glRotatef(cameraAngleY, 0, 1, 0);   // heading




//    //render
//    /*
//    float pixels[] = {
//        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
//    };
//    glBindTexture(GL_TEXTURE_2D, gl_tex);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
//    */
//    glBindTexture(GL_TEXTURE_2D, gl_tex);
//    glBegin(GL_QUADS);
//    glNormal3f(0, 0, 1);
//    //glColor4f(0.5, 0.5, 0.5, 0.5);
//    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
//    glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 0.0f);
//    glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 0.0f);
//    glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f,  1.0f, 0.0f);
//    glEnd();


//    glBegin(GL_TRIANGLES);
//    glNormal3f(0, 0, 1);
//    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 1.0f);
//    glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 1.0f);
//    glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 1.0f);
//    glEnd();
//    //glBindTexture(GL_TEXTURE_2D, 0);


//    glutSwapBuffers();
//    glutPostRedisplay();
//}
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

