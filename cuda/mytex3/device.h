#ifndef _CREATEIMG_
#define _CREATEIMG_

#define uint unsigned int
#include <cuda_runtime_api.h>
//#include <cuda_gl_interop.h>

//extern "C" void setKernel(cudaSurfaceObject_t outputSurfObj,int width, int height);
//extern "C" void mydraw (cudaSurfaceObject_t sf, float time,unsigned int width, unsigned height);

struct Image
{
    void                   *h_data;
    cudaExtent              size;
    cudaResourceType        type;
    cudaArray_t             dataArray;
    cudaMipmappedArray_t    mipmapArray;
    cudaTextureObject_t     textureObject;

    Image()
    {
        memset(this,0,sizeof(Image));
    }
};
#endif
