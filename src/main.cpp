#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <iostream>
#include "shaders/shader.h"

#define PARTICLES 10
struct particleSystem
{
  glm::vec2 pos[PARTICLES];
  glm::vec2 vel[PARTICLES];
  glm::vec3 color[PARTICLES];
  int count;
};

struct screenPartNode
{
  screenPartNode* children[4] = {nullptr, nullptr, nullptr, nullptr};
  particleSystem* particles = nullptr;
};

struct mousePosition
{
  double x;
  double y;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
bool processMouseInput(GLFWwindow *window, mousePosition *mousePosition);
void genQuad(float* quad, glm::vec2* positions, float raggio);
GLFWwindow* createWindow();
void checkForCollisions(particleSystem* particles, float radius);
void applyForce(particleSystem* particles, glm::vec2 directionPoint, float intensity);
void generateTree(screenPartNode* node, particleSystem* particles, float minX, float maxX, float minY, float maxY);
void freeTree(screenPartNode* node);
int viewportWidth = 1000;
int viewportHeight = 1000;

int main()
{
  GLFWwindow *window = createWindow();

  Shader shader("/home/luca/Projects/game/src/shaders/glsl/vertexShader.vs", "/home/luca/Projects/game/src/shaders/glsl/fragmentShader.fs");
  shader.use();

  particleSystem particles;

  float raggio = 0.01f;
  shader.setFloat("radius", raggio);
  srand(time(0));
  float lowerBoundScreenNormalized = -1.0f + raggio * 2;
  float upperBoundScreenNormalized =  1.0f - raggio * 2;
  for(int i = 0; i < PARTICLES; i++)
  {
    float cx = lowerBoundScreenNormalized + 2 * upperBoundScreenNormalized * (float)rand()/RAND_MAX;
    float cy = lowerBoundScreenNormalized + 2 * upperBoundScreenNormalized * (float)rand()/RAND_MAX;
    particles.pos[i] = glm::vec2(cx, cy);
    particles.vel[i].x = -0.2f + 0.4f * (float)rand()/RAND_MAX;
    particles.vel[i].y = -0.2f + 0.4f * (float)rand()/RAND_MAX;
    particles.color[i].x = 1.0f * (float)rand()/RAND_MAX;
    particles.color[i].y = 1.0f * (float)rand()/RAND_MAX;
    particles.color[i].z = 1.0f * (float)rand()/RAND_MAX;
  }

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  unsigned int VBOquad, VBOcolors;
  glGenBuffers(1, &VBOquad);
  glGenBuffers(1, &VBOcolors);

  float* quad = (float*)malloc(PARTICLES*24 * sizeof(float));

  float quadColors[PARTICLES * 24];
  for(int i = 0; i < PARTICLES; i++)
  {
    for(int x = 0; x < 6; x++)
    {
      quadColors[i*18 + x*3  ] = particles.color[i].x;
      quadColors[i*18 + x*3+1] = particles.color[i].y;
      quadColors[i*18 + x*3+2] = particles.color[i].z;
    }
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBOquad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PARTICLES * 24, quad, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PARTICLES * 18, quadColors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);

  float lastFrameTime;
  float deltaFrameTime = glfwGetTime();

  mousePosition mouse;

  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    if(processMouseInput(window, &mouse))
    {
      applyForce(&particles, glm::vec2(mouse.x, mouse.y), 1 * deltaFrameTime);
    }
    glfwSwapBuffers(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();

    // get lastFrameTime
    deltaFrameTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();

    // update particles
    // applyForce(&particles, glm::vec2(0.5f, 0.5f), 1 * deltaFrameTime);
    // applyForce(&particles, glm::vec2(-0.5f, -0.5f), 1 * deltaFrameTime);
    // create tree to easily handle more particles
    // screenPartNode father;
    // generateTree(&father, &particles, 0, 1, 0, 1);
    checkForCollisions(&particles, raggio);
    for(int i = 0; i < PARTICLES; i++)
    {
      particles.pos[i].x += particles.vel[i].x * deltaFrameTime;
      if(particles.pos[i].x <= -1 + raggio || particles.pos[i].x >= 1 - raggio)
        particles.vel[i].x *= -1;
      particles.pos[i].y += particles.vel[i].y * deltaFrameTime;
      if(particles.pos[i].y <= -1 + raggio || particles.pos[i].y >= 1 - raggio)
        particles.vel[i].y *= -1;
    }

    // freeTree(&father);
    // generate the quad
    genQuad(quad, particles.pos, raggio);
    // buffer data to VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBOquad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PARTICLES * 24, quad, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // draw
    glDrawArrays(GL_TRIANGLES, 0, PARTICLES*6);


  }

  free(quad);
  glDeleteBuffers(1, &VBOquad);
  glDeleteBuffers(1, &VBOcolors);
  glDeleteVertexArrays(1, &VAO);
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

GLFWwindow* createWindow()
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
    exit(-1);
  }
  glfwMakeContextCurrent(window);

  // init GLAD to manage function pointers for OpenGL
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    exit(-1);
  }

  // sets viewport for OpenGL
  glViewport(0, 0, viewportWidth, viewportHeight);
  // sets the callback function to update OpenGL viewport when the window is resized
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return window;
}

void genQuad(float* quad, glm::vec2* positions, float raggio)
{

  for(int i = 0; i < PARTICLES; i++)
  {
      // top left
      quad[i*24     ] = positions[i].x - raggio;
      quad[i*24 +  1] = positions[i].y + raggio;
      quad[i*24 +  2] = positions[i].x;
      quad[i*24 +  3] = positions[i].y;

      // top right
      quad[i*24 +  4] = positions[i].x + raggio;
      quad[i*24 +  5] = positions[i].y + raggio;
      quad[i*24 +  6] = positions[i].x;
      quad[i*24 +  7] = positions[i].y;

      // bottom left
      quad[i*24 +  8] = positions[i].x - raggio;
      quad[i*24 +  9] = positions[i].y - raggio;
      quad[i*24 + 10] = positions[i].x;
      quad[i*24 + 11] = positions[i].y;

      // top right
      quad[i*24 + 12] = positions[i].x + raggio;
      quad[i*24 + 13] = positions[i].y + raggio;
      quad[i*24 + 14] = positions[i].x;
      quad[i*24 + 15] = positions[i].y;

      // bottom right
      quad[i*24 + 16] = positions[i].x + raggio;
      quad[i*24 + 17] = positions[i].y - raggio;
      quad[i*24 + 18] = positions[i].x;
      quad[i*24 + 19] = positions[i].y;

      // bottom left
      quad[i*24 + 20] = positions[i].x - raggio;
      quad[i*24 + 21] = positions[i].y - raggio;
      quad[i*24 + 22] = positions[i].x;
      quad[i*24 + 23] = positions[i].y;
  }

}

void checkForCollisions(particleSystem* particles, float radius)
{
  for(int i = 0; i < PARTICLES; i++)
  {
    for(int j = i+1; j < PARTICLES; j++)
    {
      // glm::vec2 gravity = glm::normalize(particles->pos[i] - particles->pos[j]) * 0.00001f;
      // particles->vel[i] -= gravity;
      // particles->vel[j] -= (gravity * -1.0f);
      float dx = particles->pos[i].x - particles->pos[j].x;
      float dy = particles->pos[i].y - particles->pos[j].y;
      float dSquared = dx * dx + dy * dy;
      bool intersect = dSquared < 4 * radius * radius;
      if(intersect)
      {
        // calculate the normal and tangent vector relative to the point of collision
        glm::vec2 delta = particles->pos[i] - particles->pos[j];
        glm::vec2 normal = glm::normalize(delta);
        glm::vec2 tangent = glm::vec2(-normal.y, normal.x);

        // move the particles so that they do not overlap
        glm::vec2 overlapLenght = glm::normalize(delta) * (radius * 2 - glm::length(delta));
        particles->pos[i] = particles->pos[i] + overlapLenght * 0.5f;
        particles->pos[j] = particles->pos[j] - overlapLenght * 0.5f;

        // initial velocities
        glm::vec2 vi = particles->vel[i];
        glm::vec2 vj = particles->vel[j];

        // velocities projection along normal and tangent
        float vi_n = vi.x *  normal.x + vi.y *  normal.y;
        float vi_t = vi.x * tangent.x + vi.y * tangent.y;
        float vj_n = vj.x *  normal.x + vj.y *  normal.y;
        float vj_t = vj.x * tangent.x + vj.y * tangent.y;

        // I am assuming both particles have the same mass
        // so they're normal velocity is exchanged
        // apply some dampening after collision
        float vi_n_after = vj_n * 0.9f;
        float vj_n_after = vi_n * 0.9f;



        // compose the new velocities after collision
        particles->vel[i] = vi_n_after * normal + vi_t * tangent;
        particles->vel[j] = vj_n_after * normal + vj_t * tangent;
      }
    }
  }
}

void applyForce(particleSystem* particles, glm::vec2 directionPoint, float intensity)
{
  for(int i = 0; i < PARTICLES; i++)
  {
    glm::vec2 forceDirection = glm::normalize(directionPoint - particles->pos[i]);
    particles->vel[i] += forceDirection * intensity;
  }
}

void generateTree(screenPartNode* node, particleSystem* particles,
                  float minX, float maxX, float minY, float maxY) {
    if (!node || !particles || particles->count == 0)
        return;

    // Suddivisione solo se ci sono abbastanza particelle
    if (particles->count <= 500) {
        node->particles = (particleSystem*)malloc(sizeof(particleSystem));
        *node->particles = *particles; // copia contenuto
        for (int i = 0; i < 4; i++)
          node->children[i] = nullptr; // sicuro per freeTree
        return;
    }

    // Calcolo centro schermo
    float midX = (minX + maxX) / 2.0f;
    float midY = (minY + maxY) / 2.0f;

    // Alloca nuovi nodi figli
    for (int i = 0; i < 4; i++) {
        node->children[i] = (screenPartNode*)malloc(sizeof(screenPartNode));
        *node->children[i] = {}; // inizializza a zero
    }

    // Alloca nuovi sistemi particellari
    particleSystem* p[4];
    for (int i = 0; i < 4; i++) {
        p[i] = (particleSystem*)malloc(sizeof(particleSystem));
        p[i]->count = 0;
    }

    // Smistamento particelle nei 4 quadranti
    for (int i = 0; i < particles->count; i++) {
        float x = particles->pos[i].x;
        float y = particles->pos[i].y;

        int index;
        if (x <= midX && y <= midY)
            index = 0; // bottom-left
        else if (x > midX && y <= midY)
            index = 1; // bottom-right
        else if (x <= midX && y > midY)
            index = 2; // top-left
        else
            index = 3; // top-right

        int c = p[index]->count;
        if (c < PARTICLES) {
            p[index]->pos[c] = particles->pos[i];
            p[index]->vel[c] = particles->vel[i];
            p[index]->color[c] = particles->color[i];
            p[index]->count++;
        }
        // Altrimenti: overflow! Potresti loggare un errore o gestirlo meglio
    }

    // Ricorsione solo se necessario
    if (p[0]->count > 0)
        generateTree(node->children[0], p[0], minX, midX, minY, midY);
    if (p[1]->count > 0)
        generateTree(node->children[1], p[1], midX, maxX, minY, midY);
    if (p[2]->count > 0)
        generateTree(node->children[2], p[2], minX, midX, midY, maxY);
    if (p[3]->count > 0)
        generateTree(node->children[3], p[3], midX, maxX, midY, maxY);
}


void freeTree(screenPartNode* node) {
    if (!node) return;

    // Libera ricorsivamente i figli validi
    for (int i = 0; i < 4; i++) {
        if (node->children[i])
            freeTree(node->children[i]);
    }

    // Libera particelle se esistono
    if (node->particles)
        free(node->particles);

    free(node);
}

bool processMouseInput(GLFWwindow *window, mousePosition *mouse)
{
  int mouse1State = glfwGetMouseButton(window, 0);
  if(GLFW_PRESS == mouse1State)
  {
    glfwGetCursorPos(window, &(mouse->x), &(mouse->y));
    mouse->x = (mouse->x - viewportWidth/2.0f) / (viewportWidth/2.0f);
    mouse->y = -(mouse->y - viewportHeight/2.0f) / (viewportHeight/2.0f);
  }

  return mouse1State == GLFW_PRESS;
}
