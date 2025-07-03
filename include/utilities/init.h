#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *createWindow(int width, int height, const char *title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void terminate(GLFWwindow *window);