#include <structures/Block.h>
#include <engine/Texture.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/Shader.h>

using namespace glm;

Block::Block(ivec3 cubepos, Shader* s) : cubePosition{cubepos}, program{s}
{

}


void Block::renderBlock(){

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glad_glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    mat4 model = mat4(1.0f);
    model = translate(model, vec3(cubePosition));
    program->uniformMat4("model", model);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}
