#ifndef BEE_H
#define BEE_H

#include "raylib.h"

class Bee
{
    public:
        Vector2 position;
        float speed;
        bool movingRight;
        Texture2D texture;

        // Constructor
        Bee(bool movingRight = true, float x = 100, float y = 100, float speed = 100);

        void Update(float deltaTime);
        void Draw();
        void Unload();
        Rectangle GetCollider();
};

#endif