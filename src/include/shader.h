#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getID() const;
    void setMat4(const std::string& name, const glm::mat4 &mat) const;
private:
    GLuint shaderID;

    std::string readFile(const std::string& path) const;
    void checkCompileErrors(GLuint shader, const std::string& type) const;
};

#endif //SHADER_H
