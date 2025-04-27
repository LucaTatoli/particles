#include "player.h"

Player::Player()
{
  posX = 0;
  posY = 0;
  vX = 0;
  vY = 0;
}

Player::Player(float posX, float posY)
{
  this->posX = posX;
  this->posY = posY;
  vX = 0;
  vY = 0;
}

void Player::update()
{
  posX += vX;
  posY += vY;
}

void Player::setVelocity(float vX, float vY)
{
  this->vX = vX;
  this->vY = vY;
}
