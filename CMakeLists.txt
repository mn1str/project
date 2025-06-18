cmake_minimum_required(VERSION 3.10)
project(MiniEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

find_package(OpenGL REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(MiniEngine ${SOURCES})

target_include_directories(MiniEngine PRIVATE external/glad/include)
target_include_directories(MiniEngine PRIVATE external/glfw/include)
target_include_directories(MiniEngine PRIVATE external/glm/include)
target_link_libraries(MiniEngine PRIVATE glfw OpenGL::GL glad glm::glm)
