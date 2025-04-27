#include "rectangle.hpp"
#include <stdlib.h>

void Rectangle::initEntity()
{
  vertices_size = 20;
  vertices = (float*)calloc(vertices_size, sizeof(float));

  vertices[ 0] = -0.50f; vertices[ 1] = -0.50f; vertices[ 2] = 0.00f; vertices[ 3] = 0.0f; vertices[ 4] = 0.0f;
  vertices[ 5] =  0.50f; vertices[ 6] = -0.50f; vertices[ 7] = 0.00f; vertices[ 8] = 1.0f; vertices[ 9] = 0.0f;
  vertices[10] =  0.50f; vertices[11] =  0.50f; vertices[12] = 0.00f; vertices[13] = 1.0f; vertices[14] = 1.0f;
  vertices[15] = -0.50f; vertices[16] =  0.50f; vertices[17] = 0.00f; vertices[18] = 0.0f; vertices[19] = 1.0f;

  vertices_world = (float*)calloc(vertices_size, sizeof(float));

  vertices_world[ 0] = -0.50f; vertices_world[ 1] = -0.50f; vertices_world[ 2] = 0.00f; vertices_world[ 3] = 0.0f; vertices_world[ 4] = 0.0f;
  vertices_world[ 5] =  0.50f; vertices_world[ 6] = -0.50f; vertices_world[ 7] = 0.00f; vertices_world[ 8] = 1.0f; vertices_world[ 9] = 0.0f;
  vertices_world[10] =  0.50f; vertices_world[11] =  0.50f; vertices_world[12] = 0.00f; vertices_world[13] = 1.0f; vertices_world[14] = 1.0f;
  vertices_world[15] = -0.50f; vertices_world[16] =  0.50f; vertices_world[17] = 0.00f; vertices_world[18] = 0.0f; vertices_world[19] = 1.0f;

  indices_size = 6;
  indices = (unsigned int*)calloc(indices_size, sizeof(unsigned int));

  indices[0] = 0; indices[1] = 1; indices[2] = 2;
  indices[3] = 2; indices[4] = 0; indices[5] = 3;
}
