cmake_minimum_required(VERSION 2.8)
project(pbo)
set(CMAKE_PREFIX_PATH 
	"C:/openGL/freeglut/include"
	"C:/openGL/glew-1.9.0/include"
	)
set(CMAKE_LIBRARY_PATH 
	"C:/openGL/freeglut/lib/x64"
	"C:/openGL/glew-1.9.0/lib"
	)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	message(glew_inc= ${GLEW_INCLUDE_DIRS})
	message(glew_lib= ${GLEW_LIBRARIES})
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
	message(glut_inc=${GLUT_INCLUDE_DIR})
	message(glut_lib=${GLUT_LIBRARIES})
endif()

find_package(CUDA)

# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_20,code=sm_20)
# add sources files
set(SRCS
	main.cpp
	device.h
        device.cu
	)
cuda_add_executable(pbo ${SRCS})

message(cuda_toolkit= ${CUDA_TOOLKIT_ROOT_DIR} )
message(cuda_inc= ${CUDA_INCLUDE_DIRS})
message(cuda_lib= ${CUDA_LIBRARIES})

include_directories( 
	${CUDA_INCLUDE_DIRS}	
	${CUDA_TOOLKIT_ROOT_DIR}
	${GLUT_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
)
target_link_libraries(pbo 
	${GLUT_LIBRARIES}
	${GLEW_LIBRARIES}
	)
