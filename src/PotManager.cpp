#include "PotManager.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>

PotManager::PotManager(int screenWidth, int screenHeight, int initialPotCount)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->initialPotCount = initialPotCount;

    potTexture = LoadTexture("assets/textures/plantpot.png");
    plantTexture = LoadTexture("assets/textures/yellowflower.png");
}

void PotManager::Update(float deltaTime)
{

}

void PotManager::Draw()
{
    for (auto &pot : pots)
    {
        pot.Draw(potTexture, plantTexture);
    }
}

void PotManager::Unload()
{
    for (auto &pot : pots)
    {
        pot.Unload(potTexture, plantTexture);
    }
}

void PotManager::SpawnInitialPots()
{
    std::cout << "Spawning pots...\n";

    for (int i = 0; i < initialPotCount; i++)
    {
        bool validPos = false;

        while (!validPos)
        {
            validPos = true;
            float x = GetRandomValue(0, screenWidth);
            float y = GetRandomValue(0, screenHeight);

            if (x < 40 || x > (screenWidth - 80) ||
                y < 80 || y > (screenHeight - 80))
            {
                validPos = false;
            }

            Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

            if (Vector2Distance({x, y}, center) < 80)
            {
                validPos = false;
            }

            for (auto &pot : pots)
            {
                if (fabs(x - pot.position.x) < 80 &&
                    fabs(y - pot.position.y) < 80)
                {
                    validPos = false;
                    break;
                }
            }

            if (validPos)
            {
                pots.push_back(Flowerpot(x, y, true));
                std::cout << "Pot spawned\n";
            }
        }
    }
}

void PotManager::SpawnNewPot()
{

}