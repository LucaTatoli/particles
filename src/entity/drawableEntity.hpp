#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "../shaders/shader.h"
#include "../sprite/sprite.hpp"

class DrawableEntity
{
  private:
    unsigned int EBO, VBO, VAO;
    glm::vec4 color;
    void alignTextureCoordinate();
  protected:
    float *vertices, *vertices_world;
    unsigned int *indices;
    unsigned int vertices_size, indices_size;
    float scaleX = 1.0f, scaleY = 1.0f;
    Sprite* sprite;
    void loadTexture(bool repeat);
    virtual void initEntity() = 0;
  public:
    DrawableEntity(const char* texturePath);
    DrawableEntity(const char* texturePath, int width, int height, int frames, int fps);
    DrawableEntity();
    float posX, posY;
    unsigned int getVAO();
    void update();
    void processEntityInput(GLFWwindow* window);
    void destroy();
    void bindVAOAndBuffers();
    void draw(Shader shader);
    void setScaleX(float scaleX);
    void setScaleY(float scaleY);
    void initialize();
    void setColor(glm::vec4);
};

#endif
