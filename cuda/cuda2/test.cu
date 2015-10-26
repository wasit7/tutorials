#include "test.h"
#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/sequence.h>

template<typename T>
struct Fun
{
        __device__ T operator()(T t1, T t2)
        {
            auto result = t1+t2;
            return result;
        }
};

int run()
{
    const int N = 100;
    thrust::device_vector<int> vec(N);
    thrust::sequence(vec.begin(),vec.end());
    auto op = Fun<int>();
    return thrust::reduce(vec.begin(),vec.end(),0,op);
}