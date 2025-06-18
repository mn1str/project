#include "engine/Shader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath){
    std::string vsc, fsc;
    std::ifstream vStream, fStream;
    std::stringstream vCode, fCode;

    vStream.open(vertexShaderPath);
    fStream.open(fragmentShaderPath);

    vCode << vStream.rdbuf();
    fCode << fStream.rdbuf();

    vStream.close();
    fStream.close();
    vsc = vCode.str();
    fsc = fCode.str();

    const char *vertexShaderCode = vsc.c_str();
    const char *fragmentShaderCode = fsc.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    logInfo(vertexShader, 0);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    logInfo(fragmentShader, 0);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    logInfo(programID, 1);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

unsigned int Shader::getID(){
    return programID;
}

void Shader::logInfo(unsigned int ID, unsigned int type){
    int success;
    char infoLog[1024];
    if(!type){
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if(!success){
            glad_glGetShaderInfoLog(ID, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILE " << infoLog << '\n';
        }
    } else{
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success){
            glad_glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINK " << infoLog << '\n';
        }
    }
}


void Shader::uniformMat4(const char *name, glm::mat4 mat){
    unsigned int ID = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(ID, 1, GL_FALSE, glm::value_ptr(mat));
}
