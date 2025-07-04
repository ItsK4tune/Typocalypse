cmake_minimum_required(VERSION 3.10)
project(Project_T)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Build glad
add_library(glad STATIC src/glad.c)

# GLOB các .cpp file trong src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/glad.c")

# In debug các thư viện .lib tìm được
file(GLOB LIBFILES "${CMAKE_SOURCE_DIR}/lib/*.lib")
message(STATUS "Found .lib files:")
foreach(lib ${LIBFILES})
    message(STATUS "  ${lib}")
endforeach()

# Tập hợp source
set(SOURCES main.cpp ${SRC_FILES})

# Build executable
add_executable(Project_T ${SOURCES})

# Thêm thư mục chứa file .lib hoặc .a
link_directories("${CMAKE_SOURCE_DIR}/lib")

# Tùy theo compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Compiler: MSVC")

    target_compile_definitions(Project_T PRIVATE GLFW_STATIC)
    target_link_libraries(Project_T glad "${CMAKE_SOURCE_DIR}/lib/glfw3.lib" opengl32)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Compiler: GCC/Clang")

    target_link_libraries(Project_T glad glfw3dll opengl32)
    target_link_options(Project_T PRIVATE -mconsole)
endif()
