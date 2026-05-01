#include <print>
#include <fstream>
#include <sstream>
#include "shader.h"

Shader::~Shader() {
    glDeleteProgram(m_program);
}

Shader::Shader(const std::string& path): m_shaderSourcePath(path) {
    std::string baseSource = readFile(m_shaderSourcePath);
    baseSource = resolveImports(baseSource, m_shaderSourcePath);

    auto vertexSource = injectDefine(baseSource, "VERTEX");
    auto fragmentSource = injectDefine(baseSource, "FRAGMENT");
    auto vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    auto fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    m_program = linkProgram({vertexShader, fragmentShader});
}

GLint Shader::getUniformLocation(std::string& name) {
    auto it = m_uniformLocations.find(name);
    if (it != m_uniformLocations.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location == -1) {
        std::println(stderr, "Warning: Uniform '{}' not found in shader '{}'", name, m_shaderSourcePath);
    }

    m_uniformLocations[name] = location;
    return location;
}

GLint Shader::getResourceLocation(std::string& name) {
    auto it = m_resourceLocations.find(name);
    if (it != m_resourceLocations.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location == -1) {
        std::println(stderr, "Warning: Resource '{}' not found in shader '{}'", name, m_shaderSourcePath);
    }

    m_resourceLocations[name] = location;
    return location;
}

std::string Shader::readFile(std::string& path) const {
    std::string content = "";
    std::ifstream file(path);

    if (file.is_open()) {
        std::stringstream sstr;
        sstr << file.rdbuf();
        content = sstr.str();
    }

    return content;
}

GLuint Shader::linkProgram(std::vector<GLuint> shaders) const {
    GLuint program = glCreateProgram();
    for (GLuint shader : shaders) {
        glAttachShader(program, shader);
    }

    GLint success;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        std::println(stderr, "Shader program link error: \n{}", log);
    }

    for (GLuint shader : shaders) {
        glDeleteShader(shader);
    }

    return program;
}

GLuint Shader::compileShader(std::string& source, GLenum stage) const {
    GLuint shader = glCreateShader(stage);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);

    GLint success;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        std::string stageString;
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        switch (stage) {
            case GL_VERTEX_SHADER: stageString = "VERTEX"; break;
            case GL_FRAGMENT_SHADER: stageString = "FRAGMENT"; break;
            case GL_GEOMETRY_SHADER: stageString = "GEOMETRY"; break;
            default: stageString = "UNKNOWN"; break;
        };
        std::println(stderr, "{} Shader compile error: \n{}", stageString, log);
    }

    return shader;
}

std::vector<std::string> Shader::collectImports(std::string& source) const {
    std::vector<std::string> imports;
    std::istringstream stream(source);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.starts_with("#import")) {
            auto start = line.find('"');
            auto end = line.rfind('"');
            if (start != std::string::npos && end != std::string::npos && start != end) {
                imports.push_back(line.substr(start + 1, end - start - 1));
            }
        }
    }

    return imports;
}

std::string Shader::resolveImports(std::string& source, std::string& basePath) const {
    std::string baseDir = basePath.substr(0, basePath.find_last_of("/\\") + 1);

    auto imports = collectImports(source);
    if (imports.empty()) return source;

    std::string resolved = source;
    for (const auto& importPath : imports) {
        std::string fullPath = baseDir + importPath;
        std::string importSource = readFile(fullPath);

        if (importSource.empty()) {
            std::println(stderr, "Failed to import shader: {}", fullPath);
            continue;
        }

        importSource = resolveImports(importSource, fullPath);
        std::string directive = "#import \"" + importPath + "\"";
        size_t pos = resolved.find(directive);
        if (pos != std::string::npos) {
            resolved.replace(pos, directive.length(), importSource);
        }
    }

    return resolved;
}

std::string Shader::injectDefine(std::string& source, std::string define) const {
    if (source.starts_with("#version")) {
        size_t versionEnd = source.find('\n');
        return source.substr(0, versionEnd + 1) + "#define " + define + "\n" + source.substr(versionEnd + 1);
    }

    return "#define " + define + "\n" + source;
}

void Shader::use() const {
    glUseProgram(m_program);
}

void Shader::setInt(std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setBool(std::string& name, bool value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(std::string& name, glm::vec2& value) {
    glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec3(std::string& name, glm::vec3& value) {
    glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec4(std::string& name, glm::vec4& value) {
    glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setMat4(std::string& name, glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
