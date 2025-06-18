#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    void logInfo(unsigned int ID, unsigned int type);
public:
    unsigned int programID;
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

    void uniformMat4(const char *name, glm::mat4 mat);

    unsigned int getID();
};
