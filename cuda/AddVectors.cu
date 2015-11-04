#include <iostream>
#define W 640 //width of the image
#define H 480 //height of the image
__global__ void kernelAdd(int A[H][W], int B[H][W], int C[H][W]){
	int x=blockIdx.x*blockDim.x + threadIdx.x;
	int y=blockIdx.y*blockDim.y + threadIdx.y;
	C[y][x]=A[y][x]+B[y][x];//subtraction
}
int main(){
	int* h_A, h_B, h_C; //declaration pointers for host memory
	int* g_A, g_B, g_C; //pointers for global memory on the device
	//host memory allocation
	h_A = (int*) malloc (H*W*sizeof(int)); 
	h_B = (int*) malloc (H*W*sizeof(int)); 
	h_C = (int*) malloc (H*W*sizeof(int)); 
	//device memory allocation
	cudaMalloc((void**)&g_A, H*W*sizeof(int)); 
	cudaMalloc((void**)&g_B, H*W*sizeof(int));
	cudaMalloc((void**)&g_C, H*W*sizeof(int));
	for(int r=0;r<H;r++){
		for(int c=0;c<W;c++){
			h_A[r*W+c]=r*W+c;
			h_B[r*W+c]=1;
		}
	}		
	//copying h_A to g_A
	cudaMemcpy( g_A, h_A, H*W*sizeof(int),cudaMemcpyHostToDevice);
	//copying h_B to g_B
	cudaMemcpy( g_B, h_B, H*W*sizeof(int),cudaMemcpyHostToDevice);
	//define block size and grid size
	dim3 BlockSize(16,16,1);
	dim3 GridSize(W/dimBlock.x,H/dimBlock.y,1);
	//proceed the kernel function
	kernelAdd<<<GridSize,BlockSize>>>(g_A,g_B,g_C);
	//copying g_C to h_C
	cudaMemcpy(h_C,g_C,h*w*sizeof(int),cudaMemcpyDeviceToHost);
	//deallocate space in memory
	free(h_A);free(h_B);free(h_C);
	cudaFree(g_A);cudaFree(g_B);cudaFree(g_C);
}