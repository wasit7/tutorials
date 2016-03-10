//Hoare partition scheme https://en.wikipedia.org/wiki/Quicksort
#include <iostream>
using namespace std;
void swap(int &x,int &y){
    int temp=x;
    x=y;
    y=temp;
}
int partition(int A[], int lo, int hi){
    int i,j,p=A[lo]; 
    for(i=lo,j=hi;;){
        for(; A[i]<p;i++);
        for(; p<A[j];j--);
        if(i>=j) return j;
        swap(A[i],A[j]);
    }
}
void quicksort(int A[], int lo, int hi){
    if(lo<hi){
        int p=partition(A,lo,hi);
        quicksort(A,lo,p);
        quicksort(A,p+1,hi);
    }
}
int main() {
    int A[]={2,4,3,8,1,6,5,7,9,0};
    quicksort(A,0,9);
    for(int i=0;i<10;i++) cout<<A[i];
}