#include "raylib.h"
#include "Player.h"
#include "Bee.h"
#include "BeeManager.h"
#include "GameObject.h"
#include "Flowerpot.h"

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

    //--Set beeManager and player controller--
    BeeManager beeManager(screenWidth, screenHeight, 1.0f);
    Player player(screenWidth / 2, screenHeight / 2, 200);

    //--Create list of all objects--
    std::vector<GameObject*> objects;


    objects.push_back(new Flowerpot(100, 100, true));
    

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

        for (auto obj : objects)
        {
            if (CheckCollisionRecs(player.GetCollider(), obj->GetCollider()))
            {
                player.position = oldPosition;
            }
        }

        //--Check for bee collision with pots--
        for (auto &bee : beeManager.bees)
        {
            for (auto obj : objects)
            {
                Flowerpot* pot = dynamic_cast<Flowerpot*>(obj);

                if (pot)
                {
                    if (CheckCollisionRecs(bee.GetCollider(), pot->GetCollider()) && pot->hasPlant)
                    {
                        pot->hasPlant = false;
                        
                        bee.movingRight = !bee.movingRight;
                    }
                }
            }
        }

        //--Draw loop--
        BeginDrawing();
        DrawTexture(bg, 0, 0, WHITE);

        //--Draw all objects--
        for (auto obj : objects)
        {
            obj->Draw();
        }

        //--Draw entities--
        player.Draw();
        beeManager.Draw();

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

            //--Draw object collision--
            for (auto obj : objects)
            {
                Rectangle collisionBox = obj->GetCollider();

                DrawRectangleLines(
                    (int)collisionBox.x,
                    (int)collisionBox.y,
                    (int)collisionBox.width,
                    (int)collisionBox.height,
                    RED
                );
            }

            //--Draw FPS--
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, BLACK);

            //--Draw object counter--
            DrawText(TextFormat("Objects: %i", objects.size()), 10, 30, 20, BLACK);

            //--Draw bee counter--
            DrawText(TextFormat("Bees: %i", beeManager.bees.size()), 10, 50, 20, BLACK);

            //--Draw time--
            DrawText(TextFormat("Num bees passed: %i", beeManager.BeesPassed()), 10, 70, 20, BLACK);
        }

        EndDrawing();
    }


    for (auto obj : objects)
    {
        obj->~GameObject();
        delete obj;
    }

    for (auto bees : beeManager.bees)
    {
        bees.Unload();
    }

    player.Unload();
    UnloadTexture(bg);
    CloseWindow();

    return 0;
}