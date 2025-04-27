#include "shader.h"
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure istream objects can throw exepctions
  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode   = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR:SHADER:FILE_NOT_SUCCESFULLY_READ " << std::endl;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // 2. compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  //vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  //fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  //delete shaders; they're linked into our program and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, float value[3]) const
{
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value);
}

void Shader::setVec3f(const std::string &name, float f1, float f2, float f3) const
{
  glUniform3f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3);
}

void Shader::setVec3fGLM(const std::string &name, glm::vec3 vec) const
{
  glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setVec4fGLM(const std::string &name, glm::vec4 vec) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec2(const std::string &name, float value[2]) const
{
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, value);
}

void Shader::setMat4(const std::string &name, float *mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat);
}

void Shader::setMat4With2DArray(const std::string &name, float **mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat[0]);
}

void Shader::setMat4GLM(const std::string &name, glm::mat4 mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
