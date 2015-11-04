#include <stdio.h>
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "device.h"

//#include <cutil_inline.h>
//#include <cutil_gl_inline.h>

#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
unsigned int width=640;
unsigned int height=480;
GLuint positionsVBO;
struct cudaGraphicsResource* positionsVBO_CUDA;
void deleteVBO();
void displayCB();
void mouseCB(int button, int state, int x, int y){}
void mouseMotionCB(int x, int y){}
void reshapeCB(int w, int h){}
int main(int argc, char **argv){
    // Initialize OpenGL and GLUT for device 0
    // and make the OpenGL context current
    printf("debug00:\n");
    glutInit(&argc, argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(width,height);
    printf("debug01:\n");
    glutCreateWindow("CUDA OpenGL");
    glutDisplayFunc(displayCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutReshapeFunc(reshapeCB);
    // Explicitly set device 0
    printf("debug02:\n");
    printf("debug03:%d\n",
           cudaSetDevice(0));
    // Create buffer object and register it with CUDA
    glGenBuffers(1, &positionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    unsigned int size = width * height * 4 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    printf("debug10:%d\n",
           cudaGraphicsGLRegisterBuffer(&positionsVBO_CUDA,positionsVBO,cudaGraphicsMapFlagsWriteDiscard));
    // Launch rendering loop
    glutMainLoop();
}
void displayCB(){
    // Map buffer object for writing from CUDA
    float4* positions;
    cudaGraphicsMapResources(1, &positionsVBO_CUDA, 0);
    size_t num_bytes;
    cudaGraphicsResourceGetMappedPointer((void**)&positions,&num_bytes, positionsVBO_CUDA);
    // Execute kernel

    //createVertices(positions,(float)glutGet(GLUT_ELAPSED_TIME),width,height);
    // Unmap buffer object
    cudaGraphicsUnmapResources(1, &positionsVBO_CUDA, 0);
    // Render from buffer object
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glVertexPointer(4, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, width * height);
    glDisableClientState(GL_VERTEX_ARRAY);
    // Swap buffers
    glutSwapBuffers();
    glutPostRedisplay();
}
void deleteVBO(){
 cudaGraphicsUnregisterResource(positionsVBO_CUDA);
 glDeleteBuffers(1, &positionsVBO);
}
