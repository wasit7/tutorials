cmake_minimum_required(VERSION 2.8)
project(mycv)
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

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
	message(cv_inc=${OpenCV_INCLUDE_DIRS})
	message(cv_lib=${OpenCV_LIBS})
endif()

find_package(CUDA)

# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_30,code=sm_30)
# add sources files
set(SRCS
        main.cpp
	)
cuda_add_executable(mycv ${SRCS})

message(cuda_toolkit= ${CUDA_TOOLKIT_ROOT_DIR} )
message(cuda_inc= ${CUDA_INCLUDE_DIRS})
message(cuda_lib= ${CUDA_LIBRARIES})

include_directories( 
	${CUDA_INCLUDE_DIRS}	
	${CUDA_TOOLKIT_ROOT_DIR}
	${GLUT_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(
	mycv
	${GLUT_LIBRARIES}
	${GLEW_LIBRARIES}
	${OpenCV_LIBS}
	)
