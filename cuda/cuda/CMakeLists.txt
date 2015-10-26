cmake_minimum_required(VERSION 2.8)
project(CMakeCUDA)
# packages
find_package(CUDA)
# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_20,code=sm_20)
# add sources files
set(SRCS
     main.cpp
     cuda.cu
)
cuda_add_executable(CMakeCUDA ${SRCS})

#target_link_libraries(CMakeCUDA ${SOME_LIBRARY})
