#pragma once

#include <map>
#include <string>
#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "gfx/texture.h"

class Shader {
    GLuint m_program = -1;
    std::string m_shaderSourcePath = {};
    std::vector<std::string> m_importedShaderPaths = {};
    std::map<std::string, GLint> m_uniformLocations = {};
    std::map<std::string, GLint> m_resourceLocations = {};
public:
    ~Shader();
    Shader(const std::string& path);

    void use() const;
    void setInt(std::string& name, int value);
    void setBool(std::string& name, bool value);
    void setFloat(std::string& name, float value);
    void setVec2(std::string& name, glm::vec2& value);
    void setVec3(std::string& name, glm::vec3& value);
    void setVec4(std::string& name, glm::vec4& value);
    void setMat4(std::string& name, glm::mat4& value);
private:
    GLint getUniformLocation(std::string& name);
    GLint getResourceLocation(std::string& name);
    std::string readFile(std::string& path) const;
    GLuint linkProgram(std::vector<GLuint> shaders) const;
    GLuint compileShader(std::string& source, GLenum stage) const;
    std::vector<std::string> collectImports(std::string& source) const;
    std::string injectDefine(std::string& source, std::string define) const;
    std::string resolveImports(std::string& source, std::string& basePath) const;
};
