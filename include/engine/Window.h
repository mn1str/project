#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
public:
	GLFWwindow *window_ptr;
	Window(int height, int width, const char *title);
};
