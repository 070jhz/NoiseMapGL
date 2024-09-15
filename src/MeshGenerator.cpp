#include "MeshGenerator.h"
#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>

#define GL_CHECK(stmt) do { \
stmt; \
checkGLError(#stmt, __FILE__, __LINE__); \
} while (0)

void checkGLError(const char* stmt, const char* fname, int line);

// generate vertices and indices from heightmap
void generateMesh(const Terrain& terrain, std::vector<vertex>& vertices, std::vector<unsigned int>& indices) {
    const auto& heightmap = terrain.getHeightMap();
    size_t size = heightmap.size();

    float scale = 1.0f;
    float heightScale = 40.0f;

    for (size_t i=0; i<size; ++i) {
        for (size_t j=0; j<size; ++j) {
            vertex v;
            v.position={
                static_cast<float>(i) * scale,
                heightmap[i][j] * heightScale,
                static_cast<float>(j) * scale
            };
            glm::vec3 normal(0.0f, 1.0f, 0.0f);
            if (i > 0 && i < size - 1 && j > 0 && j < size - 1) {
                glm::vec3 tangentX(2.0f, heightmap[i+1][j] - heightmap[i-1][j], 0.0f);
                glm::vec3 tangentZ(0.0f, heightmap[i][j+1] - heightmap[i][j-1], 2.0f);
                normal = glm::normalize(glm::cross(tangentX, tangentZ));
            }
            v.normal = {normal.x, normal.y, normal.z};

            v.texCoords = {static_cast<float>(i) / static_cast<float>(size), static_cast<float>(j) / static_cast<float>(size)};
            vertices.push_back(v);
        }
    }
    for (size_t i=0; i<size-1; ++i) {
        for (size_t j=0; j<size-1; ++j) {
            unsigned int tl = i*size + j;
            unsigned int tr = tl + 1;
            unsigned int bl = (i+1)*size + j;
            unsigned int br = bl + 1;

            indices.push_back(tl);
            indices.push_back(bl);
            indices.push_back(tr);

            indices.push_back(tr);
            indices.push_back(bl);
            indices.push_back(br);
        }
    }
}

// initialize opengl buffers and upload vertex/index data
void initializeMesh(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(vertex)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texCoords));
    glEnableVertexAttribArray(2);
}


