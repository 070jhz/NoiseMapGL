#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "MathTypes.h"
#include "Terrain.h"
#include <vector>

void generateMesh(const Terrain& terrain, std::vector<vertex>& vertices, std::vector<unsigned int>& indices);
void initializeMesh(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, const std::vector<vertex>& vertices, const std:: vector<unsigned int>& indices);

#endif //MESHGENERATOR_H
