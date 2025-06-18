#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {

    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 up_vec;

public:

    Camera(glm::vec3, glm::vec3);


    inline glm::mat4 getViewTransformationMatrix(){
        return glm::lookAt(camera_position, camera_position + camera_front, up_vec);
    }

    void mouse_input_callback(GLFWwindow*, double, double);

    void process_keyboard_input(GLFWwindow*);


};
