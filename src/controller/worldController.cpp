#include "worldController.hpp"
#include <vector>
#include <algorithm>

WorldController::WorldController(){}

void WorldController::addEntity(DrawableEntity &e)
{
  e.initialize();
  this->entities.push_back(e);
}

void WorldController::removeEntity(DrawableEntity &e)
{
  this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(), [&e](std::reference_wrapper<DrawableEntity>& ref) {
                  return &ref.get() == &e;
              }), this->entities.end());
  e.destroy();
}

void WorldController::update()
{
  for(DrawableEntity& e : this->entities)
    e.update();
}

void WorldController::draw(Shader shader)
{
  for(DrawableEntity& e : this->entities)
    e.draw(shader);
}

void WorldController::destroy()
{
  for(DrawableEntity& e : this->entities)
    e.destroy();
}
