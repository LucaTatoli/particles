#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "drawableEntity.hpp"

class Triangle: public DrawableEntity
{
  protected:
    void initEntity() override;
  public:
    using DrawableEntity::DrawableEntity;
};

#endif
