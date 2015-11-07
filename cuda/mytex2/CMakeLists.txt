cmake_minimum_required(VERSION 2.8)
project(mytex2)
set(CMAKE_PREFIX_PATH 
	"C:/openGL/freeglut/include"
	"C:/openGL/glew-1.9.0/include"
	"C:/openGL/glfw-3.1.2/include"
	)
set(CMAKE_LIBRARY_PATH 
	"C:/openGL/freeglut/lib/x64"
	"C:/openGL/glew-1.9.0/lib"
	"C:/openGL/glfw-3.1.2/lib-vc2013"
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

if (GLFW_FOUND)
	message(glfw_inc=${GLFW_INCLUDE_DIR})
	message(glfw_lib=${GLFW_LIBRARIES})
endif()

find_package(CUDA)

# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_20,code=sm_20)
# add sources files
set(SRCS
        main.cpp
        device.cu
        device.h
	)
cuda_add_executable(mytex2 ${SRCS})

message(cuda_toolkit= ${CUDA_TOOLKIT_ROOT_DIR} )
message(cuda_inc= ${CUDA_INCLUDE_DIRS})
message(cuda_lib= ${CUDA_LIBRARIES})

include_directories( 
	${CUDA_INCLUDE_DIRS}	
	${CUDA_TOOLKIT_ROOT_DIR}
	${GLUT_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${SOIL_INCLUDE_DIRS}
)
target_link_libraries(
	mytex2
	${GLUT_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW_LIBRARIES}
	${SOIL_LIBRARIES}
	)
