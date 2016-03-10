cmake_minimum_required(VERSION 2.8)
project(wave)
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
	message(glew_inc= ${GLEW_INCLUDE_DIRS}\n)
	message(glew_lib= ${GLEW_LIBRARIES}\n)
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
	message(glut_inc=${GLUT_INCLUDE_DIR}\n)
	message(glut_lib=${GLUT_LIBRARIES}\n)
endif()

if (GLFW_FOUND)
	message(glfw_inc=${GLFW_INCLUDE_DIR}\n)
	message(glfw_lib=${GLFW_LIBRARIES}\n)
endif()
add_executable(wave main.cpp mymath.h mymath.cpp)

include_directories( 
	${CUDA_INCLUDE_DIRS}	
	${CUDA_TOOLKIT_ROOT_DIR}
	${GLUT_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${SOIL_INCLUDE_DIRS}
)
target_link_libraries(
	wave
	${GLUT_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW_LIBRARIES}
	${SOIL_LIBRARIES}
	)
