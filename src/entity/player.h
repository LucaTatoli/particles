#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
        float posX, posY, vX, vY;

        Player();
        Player(float posX, float posY);

        void update();
        void setVelocity(float vX, float vY);

};

#endif
