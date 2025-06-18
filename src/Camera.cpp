#include "glm/fwd.hpp"
#include <engine/Camera.h>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>



using namespace glm;

Camera::Camera(vec3 cp, vec3 cf) : camera_position(cp), camera_front(normalize(cf)), up_vec{vec3(0.0f, 1.0f, 0.0f)}{

}


void Camera::process_keyboard_input(GLFWwindow* window){
    float camera_speed = 0.05f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera_position += camera_speed * camera_front;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera_position -= camera_speed * camera_front;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera_position += normalize(cross(camera_front, up_vec)) *camera_speed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera_position -= normalize(cross(camera_front, up_vec)) *camera_speed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera_position += up_vec * camera_speed;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        camera_position -= up_vec * camera_speed;
    }
}
