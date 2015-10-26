//cuda.cu
//simple CUDA functions
//by Wasit 20-8-2011
#include <stdio.h>
#include <cuda_runtime.h>
//memory allocation on device side
extern "C" void CUDA_Constructor(int** g_A,int** g_B,int size){
    cudaMalloc(g_A,sizeof(int)*size);
    cudaMalloc(g_B,sizeof(int)*size);
}
//copying data from host to device
extern "C" void CUDA_SetData(int* g_dist, int* h_src,int size){
    cudaMemcpy(g_dist,h_src,sizeof(int)*size,cudaMemcpyHostToDevice);
}
//CUDA Kernel block and thread ID are indicated by blockIdx and threadIdx, respectively
__global__ void Kernel_Add(int* g_A,int* g_B){
    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    g_A[x]=g_A[x]+g_B[x];
}
//Addition function
//number of thread and block is set before call Kernel
extern "C" void CUDA_Add(int* g_A,int* g_B,int size){
    int threadnum=16;
    int blocknum=size/threadnum;
    Kernel_Add<<<threadnum,blocknum>>>(g_A,g_B);
}
//read data back to host
extern "C" void CUDA_GetData(int* h_dist, int* g_src,int size){
    cudaMemcpy(h_dist,g_src,sizeof(int)*size,cudaMemcpyDeviceToHost);
}
