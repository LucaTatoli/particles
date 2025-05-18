#include "drawableEntity.hpp"
#include <stdlib.h>
#include "../../include/stb_image.h"
#include <iostream>

DrawableEntity::DrawableEntity()
{
  width = 1.0f;
  height = 1.0f;
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

DrawableEntity::DrawableEntity(float width, float height)
{
  this->width = width;
  this->height = height;
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawableEntity::initialize()
{
  initEntity();
  bindVAOAndBuffers();
}

void DrawableEntity::bindVAOAndBuffers()
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2, &this->pos, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

unsigned int DrawableEntity::getVAO()
{
  return VAO;
}

void DrawableEntity::update()
{
  pos.x += velocity.x;
  pos.y += velocity.y;
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2, &this->pos, GL_STATIC_DRAW);
}

void DrawableEntity::processEntityInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    pos.y += 0.01f;
  if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    pos.y -= 0.01f;
  if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    pos.x -= 0.01f;
  if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    pos.x += 0.01f;
}

void DrawableEntity::draw(Shader shader)
{
  shader.setBool("drawTexture", false);
  shader.setVec4fGLM("color", color);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);
}

void DrawableEntity::setColor(glm::vec4 color)
{
  this->color = color;
}
