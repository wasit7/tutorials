#include <stdio.h>
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

//#include <cutil_inline.h>
//#include <cutil_gl_inline.h>

#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>

bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int frame=0;
int timebase=0;

GLuint PBO;
GLuint texid;   // texture
struct cudaGraphicsResource* Resource_CUDA;//PBO resoucre
unsigned int width=16;
unsigned int height=16;//size of texture

//callback functions
void displayCB(void);
void mouseCB(int button, int state, int x, int y);
void mouseMotionCB(int x, int y);
void reshapeCB(int w, int h);

extern "C" void createImg(GLubyte* positions,float time,unsigned int width,unsigned height);

void main(int argc, char **argv) {
	//cudaSetDevice(cutGetMaxGflopsDeviceId());
    //cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
	cudaSetDevice(0);
    cudaGLSetGLDevice(0);
	//init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
	glutInitWindowSize(512,512);
	glutCreateWindow("test VBO");
	glutDisplayFunc(displayCB);
	glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
	glutReshapeFunc(reshapeCB);
	//init gl
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//init glew
	GLenum err = glewInit(); //this line is important inorder to use glew functions sucs glGenBuffers().
	if (GLEW_OK != err){
	  printf( "Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	
	//init PBO
	glGenBuffersARB(1,&PBO);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB,PBO);
	unsigned int size=width*height*4*sizeof(unsigned char);
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB,size,0,GL_DYNAMIC_DRAW);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB,0);
	cudaGraphicsGLRegisterBuffer( &Resource_CUDA, PBO, cudaGraphicsMapFlagsWriteDiscard);

	// create texture for display
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

	glutMainLoop();
}

void displayCB(void) {
	//cuda create data
	unsigned char* position;
	
	cudaGraphicsMapResources(1,&Resource_CUDA,0);
	size_t num_bytes;
	cudaGraphicsResourceGetMappedPointer((void**)&position,&num_bytes,Resource_CUDA);
	createImg(position,glutGet(GLUT_ELAPSED_TIME)*1e-3f,width,height);

	cudaGraphicsUnmapResources(1,&Resource_CUDA,0);

	// load texture from pbo
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, PBO);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

	 // tramsform camera
    glClearColor(1.0f,1.0f,1.0f,1.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0,0,1,0,0,0,0,1,0);
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading
	
	//render
	glBindTexture(GL_TEXTURE_2D, texid);
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

	// unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

	glutSwapBuffers();	
	glutPostRedisplay();

	//compute frame rate
	char* title= new char[20];
	frame++;
	int time=glutGet(GLUT_ELAPSED_TIME);
	float fps;
	if (time - timebase > 1000){
		fps=frame*1e3f/(float)(time-timebase);
		sprintf(title,"fps %3.1f",fps);
		glutSetWindowTitle(title);
		timebase=time;
		frame=0;
	}
}
void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

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


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += 0.2f*(x - mouseX);
        cameraAngleX += 0.2f*(y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.05f;
        mouseY = y;
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
   gluPerspective(90.0f, (float)(w)/h, 0.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}
