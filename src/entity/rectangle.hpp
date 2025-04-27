#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "drawableEntity.hpp"

class Rectangle: public DrawableEntity
{
  protected:
    void initEntity();
  public:
  using DrawableEntity::DrawableEntity;
};

#endif
