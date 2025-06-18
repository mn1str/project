#include "engine/Window.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);

GLFWwindow* createWindow(int width, int height, const char *title){
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window_ptr = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window_ptr == NULL){
		std::cerr << "Failed to create window" << '\n';
		glfwTerminate();
	}
	glfwMakeContextCurrent(window_ptr);
	glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, width, height);

	return window_ptr;
}

void framebuffer_size_callback(GLFWwindow *w, int width, int height){
	glViewport(0, 0, width, height);
}
