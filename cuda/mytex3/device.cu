//#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include "device.h"
texture<uint2, 2, cudaReadModeElementType> atlasTexture;
__global__ void kernel_render(uchar4 *d_output, uint width, uint height){
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;

    float u = x / (float) width;
    float v = y / (float) height;

    if ((x < width) && (y < height))
    {
        uchar4 color=make_uchar4(u*255,v*255,127,128);
        uint i = y * width + x;
        d_output[i] = color;
    }
}

extern "C"
void device_render(uchar4 *d_output, uint width, uint height)
{

    const dim3 blockSize(16, 16, 1);
    const dim3 gridSize(width / blockSize.x, height / blockSize.y);
    kernel_render<<<gridSize, blockSize>>>(d_output, width, height);

}
