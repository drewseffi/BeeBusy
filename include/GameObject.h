#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

class GameObject
{
public:
    Vector2 position;
    Texture2D texture;
    Rectangle collider;

    GameObject(const char* texturePath, float x, float y);

    virtual void Draw();
    virtual Rectangle GetCollider();

    virtual ~GameObject();
};

#endif