#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
class Camera {

    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 up_vec;

    float yaw = 0.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;

    inline void updateCameraFrontVec();




//helpers
    inline float cam_front_getX();
    inline float cam_front_getY();
    inline float cam_front_getZ();
public:

    Camera(glm::vec3, glm::vec3);
    Camera(glm::vec3 cp, float yaw, float pitch, float sensitivity);

    inline glm::mat4 getViewTransformationMatrix(){
        return glm::lookAt(camera_position, camera_position + camera_front, up_vec);
    }
    void mouse_input_callback(GLFWwindow*, double, double);
    void process_keyboard_input(GLFWwindow*);
    void debug(){
        std::cout << "YAW: " << yaw << '\n';
        std::cout << "PITCH: " << pitch << '\n';
        std::cout << "CAMERA FRONT VECTOR: " << camera_front.x<< ' ' <<camera_front.y << ' ' <<camera_front.z << '\n';
        std::cout << "CAMERA POS VECTOR: " << camera_position.x<< ' ' <<camera_position.y << ' ' <<camera_position.z << '\n';
        std::cout << "------------------------------------------------------------\n";
    }

};


void mouse_input_callback_dispatch(GLFWwindow*, double, double);
