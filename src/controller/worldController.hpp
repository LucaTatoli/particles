#ifndef WORLD_CONTROLLER_H
#define WORLD_CONTROLLER_H
#include <functional>
#include <vector>
#include "../entity/drawableEntity.hpp"

class WorldController
{
  private:
    std::vector<std::reference_wrapper<DrawableEntity>> entities;
  public:
    WorldController();
    void addEntity(DrawableEntity &e);
    void removeEntity(DrawableEntity &e);
    void update();
    void draw(Shader shader);
    void destroy();
};

#endif
