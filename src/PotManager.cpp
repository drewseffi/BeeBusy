#include "PotManager.h"
#include "raylib.h"
#include <iostream>
#include <cmath>

PotManager::PotManager(int screenWidth, int screenHeight, int initialPotCount)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->initialPotCount = initialPotCount;
}

void PotManager::Update(float deltaTime)
{

}

void PotManager::Draw()
{
    for (auto &pot : pots)
    {
        pot.Draw();
    }
}

void PotManager::Unload()
{
    for (auto &pot : pots)
    {
        pot.~Flowerpot();
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
            float x = GetRandomValue(0, screenWidth);
            float y = GetRandomValue(0, screenHeight);

            validPos = true;

            for (auto &pot : pots)
            {
                if (fabs(x - pot.position.x) < 40 &&
                    fabs(y - pot.position.y) < 40)
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