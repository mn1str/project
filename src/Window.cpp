#include "engine/Window.h"
#include "GLFW/glfw3.h"
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

void framebuffer_size_callback(GLFWwindow*, int width, int height){
	glViewport(0, 0, width, height);
}

void toggleFullscreen(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT){
	static bool fullscr = false;
	static int x, y;
	int count;
	GLFWmonitor **monitors = glfwGetMonitors(&count);
	GLFWmonitor *monitor = monitors[1];
	const GLFWvidmode *mode = glfwGetVideoMode(monitors[1]);
	if(fullscr){
		glfwSetWindowMonitor(window, nullptr, x, y, SCR_WIDTH, SCR_HEIGHT, 0);
		fullscr = false;
	}else{
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		fullscr = true;
	}
}
