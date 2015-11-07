//#include "device.h"
//#include <cutil.h>
//#include <cutil_math.h>
//#include <cutil_inline_runtime.h>

//#include <cutil.h>
//#include <cutil_math.h>
//#include <cutil_inline_runtime.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <curand.h>

__global__ void g_draw(cudaSurfaceObject_t sf,float time,unsigned int width,unsigned height){
    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

//    g_image[((y*width+x)*4+0)*sizeof(unsigned char)]= 125;//(int)(time*60)%255;
//    g_image[((y*width+x)*4+1)*sizeof(unsigned char)]= 255;//255*x/width;
//    g_image[((y*width+x)*4+2)*sizeof(unsigned char)]= 125;//255-255*x/width;
//    g_image[((y*width+x)*4+3)*sizeof(unsigned char)]= 105;//0;
    float4 data = make_float4(.0f, .6f, .8f, 1.0f);
    surf2Dwrite(data, sf, x * sizeof(float4), y);
}
extern "C" void mydraw(cudaSurfaceObject_t sf, float time,unsigned int width, unsigned height){
    dim3 dimBlock(32,32,1);
	dim3 dimGrid(width/dimBlock.x,height/dimBlock.y,1);
    g_draw<<<dimGrid,dimBlock>>>(sf,time,width,height);
    //cutilSafeCall( cudaThreadSynchronize() );
}
__global__ void g_setKernel(cudaSurfaceObject_t outputSurfObj,int width, int height){
    // Calculate surface coordinates
    unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < width && y < height) {
        uchar4 data;
        // Read from input surface
        data=make_uchar4(32,64,128,255);
        // Write to output surface
        surf2Dwrite(data, outputSurfObj, x * 4, y);
    }
}
extern "C" void setKernel(cudaSurfaceObject_t outputSurfObj,int width, int height){
    dim3 dimBlock(16, 16);
    dim3 dimGrid((width  + dimBlock.x - 1) / dimBlock.x,(height + dimBlock.y - 1) / dimBlock.y);
    g_setKernel<<<dimGrid, dimBlock>>>(outputSurfObj, width, height);
}

