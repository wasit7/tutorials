#ifndef _CREATEIMG_
#define _CREATEIMG_
//#include <cuda_runtime_api.h>
//#include <cuda_gl_interop.h>

extern "C" void setKernel(cudaSurfaceObject_t outputSurfObj,int width, int height);
extern "C" void mydraw (cudaSurfaceObject_t sf, float time,unsigned int width, unsigned height);
#endif
