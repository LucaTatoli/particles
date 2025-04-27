#include "drawableEntity.hpp"
#include <stdlib.h>
#include "../../include/stb_image.h"
#include <iostream>

DrawableEntity::DrawableEntity()
{
  // this->texturePath = nullptr;
  sprite = nullptr;
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

DrawableEntity::DrawableEntity(const char* texturePath)
{
  // this->texturePath = texturePath;
  sprite = new Sprite(texturePath, false);
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

DrawableEntity::DrawableEntity(const char* texturePath, int width, int height, int frames, int fps)
{
  // this->texturePath = texturePath;
  sprite = new Sprite(texturePath, false, width, height, frames, fps);
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawableEntity::initialize()
{
  initEntity();
  bindVAOAndBuffers();
  if(sprite != nullptr)
    alignTextureCoordinate();
  // if(texturePath != nullptr)
    // loadTexture(false);
}

void DrawableEntity::alignTextureCoordinate()
{
  for(unsigned int i = 3; i < vertices_size; i+=5)
  {
    vertices_world[i] /= sprite->getFrames();
  }
}

void DrawableEntity::bindVAOAndBuffers()
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices_size, this->vertices_world, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices_size, indices, GL_STATIC_DRAW);

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

  for(unsigned int i = 0; i < vertices_size; i++)
  {
    if(i%5 == 0)
      vertices_world[i] = vertices[i] * scaleX + posX;
    else if(i%5 == 1)
      vertices_world[i] = vertices[i] * scaleY + posY;
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices_size, this->vertices_world, GL_STATIC_DRAW);
}

void DrawableEntity::processEntityInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    posY += 0.01f;
  if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    posY -= 0.01f;
  if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    posX -= 0.01f;
  if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    posX += 0.01f;
}

void DrawableEntity::destroy()
{
  free(vertices);
  free(vertices_world);
  free(indices);
  delete sprite;
}

void DrawableEntity::setScaleX(float scaleX)
{
  this->scaleX = scaleX;
}

void DrawableEntity::setScaleY(float scaleY)
{
  this->scaleY = scaleY;
}

void DrawableEntity::draw(Shader shader)
{
  if(sprite != nullptr)
  {
    shader.setBool("drawTexture", true);
    shader.setFloat("texOffset", sprite->getOffset());
    glBindTexture(GL_TEXTURE_2D, sprite->getTexture());
  }
  else
  {
    shader.setBool("drawTexture", false);
    shader.setVec4fGLM("color", color);
  }
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
}

void DrawableEntity::setColor(glm::vec4 color)
{
  this->color = color;
}
