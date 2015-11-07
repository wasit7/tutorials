#include <stdio.h>
#include <stdexcept>
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

//#include "SOIL.H"
//#include "device.cu"

//#include <cutil_inline.h>
//#include <cutil_gl_inline.h>

#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
unsigned int width=128;
unsigned int height=96;
GLuint gl_tex,gl_buffer;
struct cudaGraphicsResource* cuda_tex;
cudaError e;
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

extern "C" void setKernel(cudaSurfaceObject_t outputSurfObj,int width, int height);
void check(cudaError_t ec)
{
    if (ec)
        throw std::runtime_error(cudaGetErrorString(ec));
}
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    //update gl_tex
//    float pixels[] = {
//        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
//    };
    float* pixels;
    pixels=(float*) malloc(width*height*sizeof(float)*4);
    for(unsigned int r=0;r<height;r++){
        for(unsigned int c=0;c<width;c++){
            int i=r*width+c;
            pixels[4*i+0]=float(c)/float(width);
            pixels[4*i+1]=float(r)/float(height);
            pixels[4*i+2]=0.0f;
            pixels[4*i+3]=0.5f;
        }
    }
    glBindTexture(GL_TEXTURE_2D, gl_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);


    check(
        cudaSetDevice(0)
    );\
    //cudaGraphicsGLRegisterImage(&cuda_tex,gl_tex,GL_TEXTURE_2D,cudaGraphicsMapFlagsWriteDiscard)
//    glGenBuffersARB(1,&gl_buffer);
    //glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB,gl_buffer);
    //unsigned int size=width*height*4*sizeof(unsigned char);
    //glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB,size,0,GL_DYNAMIC_DRAW);
    //glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB,0);
    check(
        cudaGraphicsGLRegisterImage(&cuda_tex, gl_tex, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsSurfaceLoadStore)
    );
    //e = cudaGraphicsGLRegisterBuffer(&cuda_tex,gl_buffer,cudaGraphicsMapFlagsWriteDiscard);
    //main loop
    printf("debug01: %p\n",cuda_tex);
    glutMainLoop();
}
void displayCB(){
    //cuda write tex
//    unsigned char* g_image;
    printf("debug02: %p\n",cuda_tex);
    check(
        cudaGraphicsMapResources(1,&cuda_tex,0)
    );
    cudaArray_t cuArray;

    check(
        cudaGraphicsSubResourceGetMappedArray(&cuArray, cuda_tex, 0, 0)
    );
    printf("debug03: %p\n",cuArray);
    // Specify surface
    struct cudaResourceDesc resDesc;
    memset(&resDesc, 0, sizeof(resDesc));
    printf("resDesc:%d,%d\n",resDesc.res.array,resDesc.resType);
    resDesc.resType = cudaResourceTypeArray;

    // Create the surface objects
    resDesc.res.array.array = cuArray;
    cudaSurfaceObject_t outputSurfObj = 0;
    cudaCreateSurfaceObject(&outputSurfObj, &resDesc);

    // Invoke kernel

    setKernel(outputSurfObj, width, height);

    //size_t num_bytes;

    //cudaGraphicsResourceGetMappedPointer((void**)&g_image,&num_bytes,cuda_tex);

    //mydraw(g_image,glutGet(GLUT_ELAPSED_TIME)*1e-3f,width,height);
    cudaDestroySurfaceObject(outputSurfObj);
    cudaGraphicsUnmapResources(1,&cuda_tex,0);
    cudaFree(cuArray);


    //glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, gl_buffer);
//    glBindTexture(GL_TEXTURE_2D, gl_tex);
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);


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
    glBindTexture(GL_TEXTURE_2D, gl_tex);
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
