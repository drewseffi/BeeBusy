#ifndef SEED_H
#define SEED_H

#include "GameObject.h"
#include "Flowerpot.h"
#include <vector>

class Seed
{
    public:
        int screenWidth;
        int screenHeight;

        Vector2 position;

        Texture2D texture;

        // Constructor
        Seed(int screenWidth, int screenHeight, std::vector<Flowerpot>& pots);

        void Draw();
        void Unload();
        Rectangle GetCollider();
};

#endif