#include "sprite.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../include/stb_image.h"
#include <iostream>

Sprite::Sprite(const char* texturePath, bool repeat)
{
  loadTexture(texturePath, repeat);
  this->frames = 1;
}

Sprite::Sprite(const char* texturePath, bool repeat, int width, int height, int frames, int fps)
{
  loadTexture(texturePath, repeat);
  this->width = width;
  this->height = height;
  this->frames = frames;
  this->fps = fps;
}

float Sprite::getOffset()
{
  if(frames == 1)
    return 0;
  int deltaTime = glfwGetTime() * 1000;
  int msPerFrame = 1000 / fps;
  return 1.0f / frames * (deltaTime / msPerFrame % frames);
}

void Sprite::loadTexture(const char* texturePath, bool repeat)
{
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  if(repeat)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
  else
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

  GLenum format;
  if (nrChannels == 1)
      format = GL_RED;
  else if (nrChannels == 3)
      format = GL_RGB;
  else if (nrChannels == 4)
      format = GL_RGBA;

  if(data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "====================" << std::endl << "Failed to load texture" << std::endl << "====================" << std::endl;
  }
  stbi_image_free(data);
}

unsigned int Sprite::getTexture()
{
  return texture;
}

int Sprite::getFrames()
{
  return frames;
}
