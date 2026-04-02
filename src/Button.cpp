#include "Button.h"

Button::Button(float x, float y, float w, float h, std::string text)
{
    bounds = {x - w / 2, y - h / 2, w, h};
    this->text = text;
}

bool Button::IsClicked()
{
    return CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::Draw()
{
    bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);

    DrawRectangleRec(bounds, hovered ? LIGHTGRAY : GRAY);

    int textWidth = MeasureText(text.c_str(), 20);

    DrawText(text.c_str(),
             bounds.x + bounds.width / 2 - textWidth / 2,
             bounds.y + bounds.height / 2 - 10,
             20,
             BLACK);
}