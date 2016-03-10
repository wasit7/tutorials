#include <iostream>
#include <algorithm>
#define LARGE 1000
using namespace std;

int F(int x, int* C){
    if(C[x]<LARGE) return C[x];
    int minch;
    if(x<=1){
        C[x]=0;
        return 0;
    }
    else{
        int i;
        minch=F(x-1,C);
        if(x%2==0){
            i=F(x/2,C);
            if(i<minch) minch=i;
        }
        if(x%3==0){
            i=F(x/3,C);
            if(i<minch) minch=i;
        }
    }
    C[x]=minch+1;
    return C[x];
}
int main(){
    int C[LARGE];
    int x;
    std::fill_n(C, LARGE, LARGE);
    cout<<"An integer can be tranformed by -1, /2, /3 (if no remainder)."<<endl;
    cout<<"The program finds the minimum number of steps to transform the number to 1."<<endl;
    cout<<"Please enter an integer:";
    cin>>x;
    cout<<"min_step: "<<F(x,C)<<endl;
    return 0;
}