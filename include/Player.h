#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player 
{
    public:
        Vector2 position;
        float speed;
        Texture2D baseTexture;
        Texture2D seedTexture;
        bool hasSeed;

        // Constructor
        Player(float x = 100, float y = 100, float speed = 100);

        void Update(float deltaTime);
        void Draw();
        void Unload();
        Rectangle GetCollider();
};

#endif