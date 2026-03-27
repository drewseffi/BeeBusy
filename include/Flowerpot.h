#ifndef FLOWERPOT_H
#define FLOWERPOT_H

#include "GameObject.h"

class Flowerpot : public GameObject
{
public:
    bool hasPlant;

    Flowerpot(float x, float y, bool hasPlant);

    void Draw(Texture2D& potTexture, Texture2D& plantTexture);
    Rectangle GetCollider() override;
    void Unload(Texture2D& potTexture, Texture2D& plantTexture);
};

#endif