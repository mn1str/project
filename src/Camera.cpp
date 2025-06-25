#include "glm/fwd.hpp"
#include <engine/Camera.h>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>



using namespace glm;

Camera::Camera(vec3 cp, vec3 cf) : camera_position(cp), camera_front(normalize(cf)), up_vec{vec3(0.0f, 1.0f, 0.0f)}{

}

Camera::Camera(vec3 cp, float yaw, float pitch, float sensitivity) : camera_position(cp), camera_front(vec3(1.0f, 0.0f, 0.0f)), up_vec{vec3(0.0f, 1.0f, 0.0f)} {
    camera_front = normalize(glm::vec3(cam_front_getX(), cam_front_getY(), cam_front_getZ()));
}

inline void Camera::updateCameraFrontVec(){
    camera_front = normalize(glm::vec3(cam_front_getX(), cam_front_getY(), cam_front_getZ()));
}

void Camera::process_keyboard_input(GLFWwindow* window){
    float camera_speed = 5.f;
    if(frameLogic != nullptr) camera_speed *=* frameLogic;
    vec3 temp = camera_front;
    temp.y = 0;
    temp = normalize(temp);
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) camera_speed *= 2.0f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera_position += camera_speed * temp;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera_position -= camera_speed * temp;
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

void Camera::mouse_input_callback(GLFWwindow* window, double x, double y){
    static float lastxpos = 0.0f;
    static float lastypos = 0.0f;
    float xpos = static_cast<float>(x);
    float ypos = static_cast<float>(y);
    float xoffset = xpos - lastxpos;
    float yoffset = lastypos - ypos;
    lastxpos = xpos;
    lastypos = ypos;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    updateCameraFrontVec();
}


void mouse_input_callback_dispatch(GLFWwindow* window, double x, double y){

    Camera *camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if(camera){
        camera->mouse_input_callback(window, x, y);
    }

}



inline float Camera::cam_front_getX(){
    return camera_front.length()*cos(radians(pitch))*cos(radians(yaw));
}
inline float Camera::cam_front_getY(){
    return camera_front.length()*sin(radians(pitch));
}
inline float Camera::cam_front_getZ(){
    return camera_front.length()*cos(radians(pitch))*sin(radians(yaw));
}
