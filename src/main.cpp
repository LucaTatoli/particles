#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "controller/worldController.hpp"
#include "entity/rectangle.hpp"
#include "shaders/shader.h"
#include "entity/triangle.hpp"
#include "../include/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int viewportWidth = 800;
int viewportHeight = 600;

int main()
{
  // init GLFW library
  glfwInit();
  // sets various options inside GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // creates window
  GLFWwindow* window = glfwCreateWindow(viewportWidth, viewportHeight, "Game", NULL, NULL);
  if(window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // init GLAD to manage function pointers for OpenGL
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // sets viewport for OpenGL
  glViewport(0, 0, viewportWidth, viewportHeight);
  // sets the callback function to update OpenGL viewport when the window is resized
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Shader shader("/home/luca/Projects/game/src/shaders/glsl/vertexShader.vs", "/home/luca/Projects/game/src/shaders/glsl/fragmentShader.fs");
  shader.use();


  WorldController worldController;
  Triangle triangle("/home/luca/Projects/game/textures/tri.png");
  triangle.posX = -0.7f;
  triangle.posY = -0.5f;
  Rectangle rectangle("/home/luca/Projects/game/textures/megaman.png", 700, 200, 4, 4);
  rectangle.setScaleX(0.25f);
  rectangle.setScaleY(0.25f);
  rectangle.posX = 1.0f;
  rectangle.posY = 1.0f;
  Rectangle rectangle1("/home/luca/Projects/game/textures/megaman.png", 700, 200, 4, 4);
  rectangle1.setScaleX(0.25f);
  rectangle1.setScaleY(0.25f);
  rectangle1.posX = -1.0f;
  rectangle1.posY = -1.0f;
  worldController.addEntity(rectangle1);

  rectangle.setColor(glm::vec4(1.0f, 0.2f, 0.1f, 1.0f));
  worldController.addEntity(triangle);
  worldController.addEntity(rectangle);

  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    triangle.processEntityInput(window);
    rectangle.processEntityInput(window);
    glfwSwapBuffers(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();

    // update viewport in vertex shader
    shader.setFloat("width", viewportWidth);
    shader.setFloat("height", viewportHeight);

    // draw
    worldController.update();
    worldController.draw(shader);

  }

  worldController.destroy();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window __attribute__((unused)), int width, int height)
{
  viewportWidth = width;
  viewportHeight = height;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
