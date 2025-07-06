cmake_minimum_required(VERSION 3.10)
project(Project_T)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/include/freetype
)

add_library(glad STATIC src/glad.c)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/glad.c")

file(GLOB LIBFILES "${CMAKE_SOURCE_DIR}/lib/*.lib")
message(STATUS "Found .lib files:")
foreach(lib ${LIBFILES})
    message(STATUS "  ${lib}")
endforeach()

set(SOURCES main.cpp ${SRC_FILES})

add_executable(Project_T ${SOURCES})

link_directories("${CMAKE_SOURCE_DIR}/lib")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Compiler: MSVC")

    add_custom_command(TARGET Project_T POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/freetype.dll"
        $<TARGET_FILE_DIR:Project_T>)
    target_compile_definitions(Project_T PRIVATE GLFW_STATIC)
    target_link_libraries(Project_T glad "${CMAKE_SOURCE_DIR}/lib/glfw3.lib" "${CMAKE_SOURCE_DIR}/lib/freetype.lib" opengl32)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Compiler: GCC/Clang")

    target_link_libraries(Project_T glad glfw3 freetype opengl32)
    target_link_options(Project_T PRIVATE -mconsole)
endif()
