#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <vector>

class Terrain {
public:
    Terrain(size_t size);

    void populateHeightMap(size_t size);
    float getHeight(size_t x, size_t y) const;
    size_t getSize() const;
    void setHeight(size_t x, size_t y, float height);
    void exportHeightMap(const std::string& filename, size_t size) const;
    void testExportMap(const std::string& filename, size_t size);
    const std::vector<std::vector<float>>& getHeightMap() const;

private:
    size_t size;
    std::vector<std::vector<float>> heightmap;

    float randomDisplacement(float scale) const;
};

#endif // TERRAIN_H

