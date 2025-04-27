#include "triangle.hpp"
#include <stdlib.h>

void Triangle::initEntity()
{
  vertices_size = 15;
  vertices = (float*)calloc(vertices_size, sizeof(float));

  vertices[ 0] = -0.50f; vertices[ 1] = -0.50f; vertices[ 2] =  0.00f; vertices[ 3] = 0.0f; vertices[ 4] = 0.0f;
  vertices[ 5] =  0.50f; vertices[ 6] = -0.50f; vertices[ 7] =  0.00f; vertices[ 8] = 1.0f; vertices[ 9] = 0.0f;
  vertices[10] =  0.00f; vertices[11] =  0.37f; vertices[12] =  0.00f; vertices[13] = 0.5f; vertices[14] = 1.0f;

  vertices_world = (float*)calloc(vertices_size, sizeof(float));

  vertices_world[ 0] = -0.50f; vertices_world[ 1] = -0.50f; vertices_world[ 2] =  0.00f; vertices_world[ 3] = 0.0f; vertices_world[ 4] = 0.0f;
  vertices_world[ 5] =  0.50f; vertices_world[ 6] = -0.50f; vertices_world[ 7] =  0.00f; vertices_world[ 8] = 1.0f; vertices_world[ 9] = 0.0f;
  vertices_world[10] =  0.00f; vertices_world[11] =  0.37f; vertices_world[12] =  0.00f; vertices_world[13] = 0.5f; vertices_world[14] = 1.0f;

  indices_size = 3;
  indices = (unsigned int*)calloc(indices_size, sizeof(unsigned int));

  indices[0] = 0; indices[1] = 1; indices[2] = 2;

  bindVAOAndBuffers();
}
