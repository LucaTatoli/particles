#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
  private:
    unsigned int texture;
    int width, height, frames, fps;
    void loadTexture(const char* texturePath, bool repeat);
  public:
    Sprite(const char* texturePath, bool repeat);
    Sprite(const char* texturePath, bool repeat, int width, int height, int frames, int fps);
    unsigned int getTexture();
    float getOffset();
    int getFrames();
};

#endif
