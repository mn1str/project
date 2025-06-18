#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* createWindow(int, int, const char*);

void toggleFullscreen(GLFWwindow*, int, int);
