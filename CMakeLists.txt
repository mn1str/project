cmake_minimum_required(VERSION 3.10)
project(MiniEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glad)

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(MiniEngine ${SOURCES})

target_include_directories(MiniEngine PRIVATE external/glad/include)
target_link_libraries(MiniEngine PRIVATE glfw OpenGL::GL glad glm::glm)
