#include "Flowerpot.h"

Flowerpot::Flowerpot(float x, float y, bool hasPlant)
    : GameObject("assets/plantpot.png", x, y)
{
    this->hasPlant = hasPlant;

    potTexture = LoadTexture("assets/plantpot.png");
    plantTexture = LoadTexture("assets/yellowflower.png");
}

void Flowerpot::Draw()
{
    Texture2D& tex = hasPlant ? plantTexture : potTexture;

    DrawTexture(
        tex,
        position.x - tex.width / 2,
        position.y - tex.height / 2,
        WHITE
    );
}

Rectangle Flowerpot::GetCollider()
{
    return {
        position.x - texture.width / 4,
        position.y - texture.height / 2,
        (float)texture.width / 2,
        (float)texture.height
    };
}

Flowerpot::~Flowerpot()
{
    UnloadTexture(potTexture);
    UnloadTexture(plantTexture);
}