#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "engine/Shader.h"
#include "engine/Texture.h"
#include "engine/Window.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <engine/Camera.h>
#include <structures/Block.h>




using namespace glm;
using namespace std;

void processInput(GLFWwindow*);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{

	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}
	GLFWwindow *window = createWindow(SCR_WIDTH, SCR_HEIGHT, "XD");

	Shader shader("resources/shaders/vertexshader", "resources/shaders/fragmentshader");
	unsigned int texture = createTexture("resources/textures/grass.jpg");
	unsigned int texture2 = createTexture("resources/textures/container.jpg");

	vector<ivec3> cubePosistions{

	};

	vector<Block> blocks;


	constexpr int TEST = 20;
	// for(int i{}; i < TEST; ++i){
	// 	for(int j{}; j < TEST; ++j){
	// 		// for(int k{}; k < TEST; ++k){
	// 			cubePosistions.push_back(ivec3(i,0.0f,j));
	// 		// }
	// 	}
	// }

	for(int i{}; i < TEST; ++i){
		for(int j{}; j < TEST; ++j){
			for(int k{}; k < TEST; ++k){
				cubePosistions.push_back(ivec3(i,j,k));
			}
		}
	}

	for(ivec3 p : cubePosistions){
		blocks.push_back(Block(vec3(p), &shader));
	}


	glUseProgram(shader.programID);
	glEnable(GL_DEPTH_TEST);


	// Camera camera{vec3(-2.0f, 4.0f, 3.0f),  -vec3(-2.0f, 4.0f, 3.0f) + vec3(0.0f, 1.0f, 0.0f)};
	Camera camera{vec3(-2.0f, 4.0f, 3.0f), -90.0f, 0.0f, 0.1f};
	glfwSetWindowUserPointer(window, &camera);
	glfwSetCursorPosCallback(window, mouse_input_callback_dispatch);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	mat4 projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
	shader.uniformMat4("projection", projection);
	float deltaTime;
	camera.frameLogic = &deltaTime;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	while(!glfwWindowShouldClose(window)){
//frame logic
		static float lastTime{};
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
//input
		processInput(window);
		camera.process_keyboard_input(window);
		camera.debug();
		std::cout << 1/deltaTime << "\n--------------------------------\n";
//clear
		shader.uniformMat4("view", camera.getViewTransformationMatrix());
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//render


		shader.uniformMat4("view", camera.getViewTransformationMatrix());

		glBindTexture(GL_TEXTURE_2D, texture);
		for(Block b : blocks){
			b.renderBlock();
		}

//xd
		glfwSwapBuffers(window);
		glfwPollEvents();



		lastTime = currentTime;






		static constexpr float fps = 0.0f;
		while(glfwGetTime() - lastTime < fps);
	}

	glDeleteProgram(shader.programID);
	glfwTerminate();
	return 0;
}

void wait(){
	float xd = static_cast<float>(glfwGetTime());
	while (glfwGetTime() - xd < 0.25f) {

	}
}

void processInput(GLFWwindow* window){
	static bool fullscr = false;
	static bool wireframe = false;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, 1);
	}
	if(glfwGetKey(window, GLFW_KEY_F11)){
		toggleFullscreen(window, SCR_WIDTH, SCR_HEIGHT);
		wait();
	}
	if(glfwGetKey(window, GLFW_KEY_C)){
		if(!wireframe){
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			wireframe = true;
		} else{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			wireframe = false;
		}
		wait();
	}
}

