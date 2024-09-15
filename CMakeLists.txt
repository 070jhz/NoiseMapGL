cmake_minimum_required(VERSION 3.28)
project(NoiseMapGL)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(libs/glm)

# Add the glad library
add_library(glad src/gl.c)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp src/shader.cpp src/Terrain.cpp src/MeshGenerator.cpp
        src/Camera.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src/include libs/glfw/include src/include/glad)
target_include_directories(glad PRIVATE src/include/glad)

link_directories(${CMAKE_SOURCE_DIR}/libs/glfw/build/src)

# Link libraries
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_SOURCE_DIR}/libs/glfw/build/src/libglfw3.a)