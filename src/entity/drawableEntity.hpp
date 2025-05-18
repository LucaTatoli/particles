#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "../shaders/shader.h"

class DrawableEntity
{
  private:
    unsigned int EBO, VBO, VAO;
    glm::vec4 color;
  protected:
    float width, height;
    virtual void initEntity() = 0;
  public:
    DrawableEntity(float width, float height);
    DrawableEntity();
    glm::vec2 pos;
    glm::vec2 velocity;
    unsigned int getVAO();
    void update();
    void processEntityInput(GLFWwindow* window);
    void bindVAOAndBuffers();
    void draw(Shader shader);
    void initialize();
    void setColor(glm::vec4);
};

#endif
