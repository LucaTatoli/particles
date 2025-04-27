#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
  public:
    //the shader program ID
    unsigned int ID;

    //constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    //use/activate the shader
    void use();
    //utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float value[3]) const;
    void setVec3f(const std::string &name, float f1, float f2, float f3) const;
    void setVec3fGLM(const std::string &name, glm::vec3 vec) const;
    void setVec4fGLM(const std::string &name, glm::vec4 vec) const;
    void setVec2(const std::string &name, float value[2]) const;
    void setMat4(const std::string &name, float *mat) const;
    void setMat4With2DArray(const std::string &name, float **mat) const;
    void setMat4GLM(const std::string &name, glm::mat4 mat) const;
};

#endif
