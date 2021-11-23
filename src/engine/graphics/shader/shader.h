#ifndef SHADER_H
#define SHADER_H

#include "../../glHeader.h"
#include <stdlib.h>

enum ShaderType 
{
    vertexType, 
    fragmentType, 
    computeType 
};

class Shader
{
private:
    const char* m_VertexPathConst;
    const char* m_FragmentPathConst;

public:
    GLuint m_ShaderID;  // program ID

    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* path, ShaderType type);
    ~Shader();

    void loadShaders();
    void loadShader(const char* shaderPath, ShaderType type);
    void enable() const;
    void disable() const;

    int getUniformLocation(const char* name);

public:
    // utility uniform functions
    void setUniformBool(const char* name, const bool value);
    void setUniform1i(const char* name, const int value);
    void setUniform1iv(const char* name, int count, const int* value);
    void setUniform1f(const char* name, const float value);
    void setUniform1fv(const char* name, int count, const float* value);
    void setUniform2f(const char* name, const glm::vec2& vector);
    void setUniform3f(const char* name, const glm::vec3& vector);
    void setUniform4f(const char* name, const glm::vec4& vector);
    void setUniformMat4(const char* name, const glm::mat4& m);
};


#endif