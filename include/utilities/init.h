#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *createWindow(int width, int height, const char *title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void character_callback(GLFWwindow *window, unsigned int codepoint);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void terminate(GLFWwindow *window);