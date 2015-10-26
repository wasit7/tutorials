#ifndef _CREATEIMG_
#define _CREATEIMG_

//#include <cutil.h>
//#include <cutil_math.h>
//#include <cutil_inline_runtime.h>

__global__ void createPixels(unsigned char* positions,float time,unsigned int width,unsigned height){
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;
    positions[((y*width+x)*4)*sizeof(unsigned char)]= 125;//(int)(time*60)%255;
    positions[((y*width+x)*4+1)*sizeof(unsigned char)]= 255;//255*x/width;
    positions[((y*width+x)*4+2)*sizeof(unsigned char)]= 125;//255-255*x/width;
    positions[((y*width+x)*4+3)*sizeof(unsigned char)]= 105;//0;

}
extern "C" void createImg(unsigned char* positions,float time,unsigned int width,unsigned height){
	dim3 dimBlock(16,16,1);
	dim3 dimGrid(width/dimBlock.x,height/dimBlock.y,1);
	createPixels<<<dimGrid,dimBlock>>>(positions,time,width,height);
    //cutilSafeCall( cudaThreadSynchronize() );
}

#endif
