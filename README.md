# 2D Particle Simulation with QuadTree

This project is a 2D particle simulation written in C++ and rendered using OpenGL.  
It was created as a toy project to experiment with real-time graphics, spatial partitioning, and basic physics simulation.

## Overview

The simulation spawns thousands of particles in a 2D space.  
Each particle has a position, velocity, and radius. The program updates their positions frame by frame and resolves collisions between particles using a **quadtree** to improve performance.

The rendering is performed with OpenGL, using custom vertex and fragment shaders to draw the particles on screen.

## Main Components

- **Particle** (`particle.cpp`, `particle.hpp`):  
  Defines the particle structure with position, velocity, color, and update logic (movement, boundary handling).

- **QuadTreeNode** (`quadTreeNode.cpp`, `quadTreeNode.hpp`):  
  Implements a quadtree data structure to subdivide the simulation space, allowing efficient collision checks among nearby particles.

- **Shader** (`shader.cpp`, `shader.h`):  
  Manages the OpenGL shaders (vertex and fragment) used to render the particles.

- **DrawableEntity** (`drawableEntity.*`):  
  Provides a base class for renderable objects. This can be extended to add other graphical elements.

- **Main Program** (`main.cpp`):  
  Initializes the OpenGL context and window, generates particles, updates the simulation in a loop, and renders each frame.

## Purpose

The main goals of this project were:

- To experiment with OpenGL for rendering many moving objects in real time
- To implement a quadtree to improve collision detection efficiency
- To explore basic multithreading (using `std::thread` for collision checks)
- To deepen understanding of real-time simulation loops

## Notes

This is an experimental and educational project, not optimized for production use.  
It focuses on learning data structures, rendering, and simulation concepts rather than providing a polished or optimized engine.

## Demo

<video src="demo/demo.mkv" controls width="600"></video>
