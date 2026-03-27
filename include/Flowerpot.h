#ifndef FLOWERPOT_H
#define FLOWERPOT_H

#include "GameObject.h"

class Flowerpot : public GameObject
{
public:
    bool hasPlant;

    Texture2D plantTexture;
    Texture2D potTexture;

    Flowerpot(float x, float y, bool hasPlant);

    void Draw() override;
    Rectangle GetCollider() override;
    ~Flowerpot();
};

#endif