//main.cpp
// simple warpper class of CUDA function.
// Vector A abd B is inititialized and transfered to the device.
// Thedevice performs addition and transfers the data back to host.
// by Wasit Limprasert created on 19-07-2011
// updated 23-08-2011: adding comment
#include <stdlib.h>
#include <stdio.h>
extern "C" void CUDA_Constructor(int** g_A,int** g_B,int size);
extern "C" void CUDA_SetData(int* g_dist, int* h_src, int size);
extern "C" void CUDA_Add(int* g_A,int* g_B,int size);
extern "C" void CUDA_GetData(int* h_dist, int* g_src,int size);
class VectorOperation{
public:
    int *h_A,*g_A;//h_A host pointer of vector A and g_A is a ponter to global memory on device.
    int *h_B,*g_B;
    int size;
    VectorOperation(int _size);
    ~VectorOperation(void){}
    void init(void);
    void SetA(int* h_src){CUDA_SetData(g_A,h_src,size);}
    void SetB(int* h_src){CUDA_SetData(g_B,h_src,size);}
    void Add(void){CUDA_Add(g_A,g_B,size);}
    void Result(void);
};
//constractor
//setting size of vectors and memory allocation on both host and device.
VectorOperation::VectorOperation(int _size){
    size=_size;
    CUDA_Constructor(&g_A,&g_B,size);
    h_A=(int*)malloc(sizeof(int)*size);
    h_B=(int*)malloc(sizeof(int)*size);
}
//initialization
//generating data for vector A and B then copy the data to device.
void VectorOperation::init(void){
    printf("A  =");
    for(int i=0;i<size;i++){
        h_A[i]=1;
        printf("%2d ",h_A[i]);
    }
    SetA(h_A);
    printf("\nB  =");
    for(int i=0;i<size;i++){
        h_B[i]=i;
        printf("%2d ",h_B[i]);
    }
    SetB(h_B);
    printf("\n");
}
//reading result,which is saved in g_A back to h_A and print out.
void VectorOperation::Result(void){
    CUDA_GetData(h_A,g_A,size);
    printf("A+B:");
    for(int i=0;i<size;i++){
        printf("%2d ",h_A[i]);
    }
    printf("\n");
}
//main
int main(){
    printf("Simple CUDA vector addition.\n");
    VectorOperation P = VectorOperation(16);
    P.init();
    P.Add();
    P.Result();
    getchar();
}
