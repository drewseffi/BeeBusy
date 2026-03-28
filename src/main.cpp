#include "raylib.h"
#include "Player.h"
#include "Bee.h"
#include "BeeManager.h"
#include "GameObject.h"
#include "Flowerpot.h"
#include "PotManager.h"
#include "Seed.h"

int main(void)
{
    //--Initialize window--
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "BeeBusy");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    bool debug = false;
    Texture2D bg = LoadTexture("assets/grass.png");

    //--Set managers and player controller--
    BeeManager beeManager(screenWidth, screenHeight, 2.0f);
    Player player(screenWidth / 2, screenHeight / 2, 200);

    PotManager potManager(screenWidth, screenHeight, 6);
    potManager.SpawnInitialPots();

    Seed seed(screenWidth, screenHeight, potManager.pots);

    //--Game loop--
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            debug = !debug;
        }

        //--Update beeManager--
        beeManager.Update(deltaTime);

        //--Check for player collision with pots--
        Vector2 oldPosition = player.position;

        player.Update(deltaTime);

        for (auto &pot : potManager.pots)
        {
            if (CheckCollisionRecs(player.GetCollider(), pot.GetPotCollider()))
            {
                player.position = oldPosition;

                if (player.hasSeed && !pot.hasPlant)
                {
                    pot.hasPlant = true;
                    player.hasSeed = false;
                }
            }
        }

        //--Check player collision with seeds--
        if (CheckCollisionRecs(player.GetCollider(), seed.GetCollider()))
        {
            player.hasSeed = true;
        }

        //--Check for bee collision with pots--
        for (auto &bee : beeManager.bees)
        {
            for (auto &pot : potManager.pots)
            {
                if (CheckCollisionRecs(bee.GetCollider(), pot.GetPotCollider()) && pot.hasPlant)
                {
                    pot.hasPlant = false;
                    
                    bee.movingRight = !bee.movingRight;
                }
                else if (CheckCollisionRecs(bee.GetCollider(), pot.GetPlantCollider()) && pot.hasPlant)
                {
                    pot.hasPlant = false;
                    
                    bee.movingRight = !bee.movingRight;
                }
            }
        }

        //--Draw loop--
        BeginDrawing();
        DrawTexture(bg, 0, 0, WHITE);

        //--Draw all pots--
        potManager.Draw();

        //--Draw entities--
        seed.Draw();
        player.Draw();
        beeManager.Draw();

        //--Show seed text above player--
        int textWidth = MeasureText("You have a plant, hurry!", 20);

        int textStartX = player.position.x - textWidth / 2;

        if (player.hasSeed)
        {
            DrawText("You have a plant, hurry!", textStartX, player.position.y - 60, 20, RED);   
        }

        //--Draw debug tools--
        if (debug)
        {
            //--Draw player collision--
            Rectangle playerCol = player.GetCollider();

            DrawRectangleLines(
                (int)playerCol.x,
                (int)playerCol.y,
                (int)playerCol.width,
                (int)playerCol.height,
                RED
            );

            //--Draw bee collision--
            for (auto bees : beeManager.bees)
            {
                Rectangle collisionBox = bees.GetCollider();

                DrawRectangleLines(
                    (int)collisionBox.x,
                    (int)collisionBox.y,
                    (int)collisionBox.width,
                    (int)collisionBox.height,
                    RED
                );
            }

            //--Draw pot collision--
            for (auto &pot : potManager.pots)
            {
                Rectangle collisionBox = pot.GetPotCollider();

                DrawRectangleLines(
                    (int)collisionBox.x,
                    (int)collisionBox.y,
                    (int)collisionBox.width,
                    (int)collisionBox.height,
                    RED
                );

                collisionBox = pot.GetPlantCollider();

                DrawRectangleLines(
                    (int)collisionBox.x,
                    (int)collisionBox.y,
                    (int)collisionBox.width,
                    (int)collisionBox.height,
                    RED
                );
            }

            Rectangle seedCol = seed.GetCollider();

            DrawRectangleLines(
                (int)seedCol.x,
                (int)seedCol.y,
                (int)seedCol.width,
                (int)seedCol.height,
                RED
            );

            //--Draw FPS--
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, BLACK);

            //--Draw pot counter--
            DrawText(TextFormat("Pots: %i", potManager.pots.size()), 10, 30, 20, BLACK);

            //--Draw bee counter--
            DrawText(TextFormat("Bees: %i", beeManager.bees.size()), 10, 50, 20, BLACK);

            //--Draw time--
            DrawText(TextFormat("Num bees passed: %i", beeManager.BeesPassed()), 10, 70, 20, BLACK);
        }

        EndDrawing();
    }

    for (auto &bees : beeManager.bees)
    {
        bees.Unload();
    }

    potManager.Unload();

    player.Unload();
    seed.Unload();
    UnloadTexture(bg);
    CloseWindow();

    return 0;
}