#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class Button
{
    public:
        Rectangle bounds;
        std::string text;

        // Constructor
        Button(float x, float y, float w, float h, std::string text);

        bool IsClicked();
        void Draw();
};

#endif