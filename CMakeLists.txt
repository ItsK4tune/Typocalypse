cmake_minimum_required(VERSION 3.10)
project(Project_T)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(glad STATIC src/glad.c)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/glad.c")

set(SOURCES main.cpp ${SRC_FILES})

add_executable(Project_T ${SOURCES})

link_directories("${CMAKE_SOURCE_DIR}/lib")

target_link_libraries(Project_T glad glfw3 opengl32)

target_link_options(Project_T PRIVATE -mconsole)