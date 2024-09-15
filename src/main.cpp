#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Terrain.h"
#include "MathTypes.h"
#include "MeshGenerator.h"
#include "shader.h"
#include "Camera.h"
Camera camera(glm::vec3(256.0f, 256.0f, 512.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -45.0f);

float lastX;
float lastY;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
}

void checkGLError(const char* stmt, const char* fname, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << err << ", at " << fname << ":" << line << " - for " << stmt << std::endl;
        exit(1);
    }
}

#define GL_CHECK(stmt) do { \
stmt; \
checkGLError(#stmt, __FILE__, __LINE__); \
} while (0)

void checkShaderCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;

            // print shader source
            GLint sourceLength;
            glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &sourceLength);
            std::vector<GLchar> source(sourceLength);
            glGetShaderSource(shader, sourceLength, nullptr, source.data());
            std::cerr << "Shader source:\n" << source.data() << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xOffset, yOffset);
}

void regenerateTerrain(Terrain& terrain, std::vector<vertex>& vertices, std::vector<unsigned int>& indices,
    unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, Shader& shader) {
    terrain.populateHeightMap(terrain.getSize());

    vertices.clear();
    indices.clear();

    generateMesh(terrain, vertices, indices);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    initializeMesh(VAO, VBO, EBO, vertices, indices);
    shader.use();
}

void processInput(GLFWwindow* window, Camera& camera, float deltaTime, bool& spaceWasPressed, Terrain& terrain, std::vector<vertex>& vertices,
    std::vector<unsigned int>& indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, Shader& shader) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard('W', deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard('S', deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard('A', deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard('D', deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!spaceWasPressed) {
            regenerateTerrain(terrain, vertices, indices, VAO, VBO, EBO, shader);
            spaceWasPressed = true;
        }
    } else {
        spaceWasPressed = false;
    }
}
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Imp", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    constexpr size_t size = 512;
    Terrain terrain(size);
    terrain.populateHeightMap(size);

    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    generateMesh(terrain, vertices, indices);

    unsigned int VAO, VBO, EBO;
    initializeMesh(VAO, VBO, EBO, vertices, indices);

    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    shader.use();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);

    // uncomment below for wireframe view
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    bool spaceWasPressed = false;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera, deltaTime, spaceWasPressed, terrain, vertices, indices, VAO, VBO, EBO, shader);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}