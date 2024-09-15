#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Terrain.h"
#include "PerlinHelpers.h"
#include <random>
#include <iostream>
#include <fstream>
#include <algorithm>

Terrain::Terrain(size_t size) :
        size(size), heightmap(size, std::vector(size, 0.0f)) {}

void Terrain::populateHeightMap(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1000.0f);
    float seed = dis(gen);

    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            float x = static_cast<float>(i) / static_cast<float>(size);
            float y = static_cast<float>(j) / static_cast<float>(size);

            // layering
            float val = 0.0f;
            float freq = 3.0f;
            float amp = 1.0f;

            for (int octave=0; octave<8; ++octave) {
                float sampleX = x * freq;
                float sampleY = y * freq;
                val += perlin(sampleX, sampleY, seed) * amp;

                freq *= 2.0f;
                amp *= 0.4f;
            }
            // contrast
            val *= 5.0f;

            // range from [-1,1] to [0,1]
            val = (val + 1.0f) * 0.5f;

            // clipping
            // val = std::clamp(val, 0.0f, 1.0f);

            heightmap[i][j]=val;
        }
    }
}


float Terrain::getHeight(size_t x, size_t y) const {
    return heightmap[x][y];
}

size_t Terrain::getSize() const {
    return size;
}


void Terrain::setHeight(size_t x, size_t y, float height) {
    heightmap[x][y]=height;
}

void Terrain::exportHeightMap(const std::string& filename, size_t size) const {
    // stbi_write_jpg(filename.c_str(), size, size, 1, &heightmap[0][0], 100);
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    file << "P5\n" << size << " " << size << "\n255\n";

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            auto pixel = static_cast<unsigned char>(heightmap[i][j]);
            file.write(reinterpret_cast<char*>(&pixel), sizeof(pixel));
        }
    }

    file.close();
}

void Terrain::testExportMap(const std::string& filename, size_t size) {
    std::ofstream file(filename);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            int pixel = static_cast<int>(heightmap[i][j]);
            file << pixel << ' ';
        }
        file << "\n";
    }
    file.close();
}

float Terrain::randomDisplacement(float scale) const {
    std::random_device rd;
     std::mt19937 gen(rd());
    std::uniform_real_distribution dis(-0.5f, 0.5f);
    return dis(gen) * scale;
}

const std::vector<std::vector<float>>& Terrain::getHeightMap() const {
    return heightmap;
}
