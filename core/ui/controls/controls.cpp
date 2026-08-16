#include "controls.h"

void Controls::CheckBox::Draw(Vector2D Position, const std::string& label, bool& value)
{
    Vector2D boxSize(8,8);

    ImVec2 mousePos = ImGui::GetIO().MousePos;

    Vector2D textPos(Position.x + boxSize.x + 8, Position.y - 3);
    Vector2D textSize(Draw::Text::GetTextWidth(ImGui::GetFont(), label.c_str()), Draw::Text::GetTextHeight(ImGui::GetFont(), label.c_str()));

    bool hoverBox = mousePos.x >= Position.x && mousePos.x <= Position.x + boxSize.x && mousePos.y >= Position.y && mousePos.y <= Position.y + boxSize.y;

    bool hoverText = mousePos.x >= textPos.x && mousePos.x <= textPos.x + textSize.x && mousePos.y >= textPos.y && mousePos.y <= textPos.y + textSize.y;

    bool hovered = hoverBox || hoverText;

    Colors textColor = hovered ? Colors(255, 255, 255, 255) : Colors(160, 160, 160, 150);

    Draw::Rect::Draw(Position, boxSize, Colors(60, 60, 60, 255));

    Draw::Text::Draw(ImGui::GetFont(), textPos, label.c_str(), textColor, false);

    if (hovered && ImGui::IsMouseClicked(0) && !InputManager::IsInputBlocked(""))
        value = !value;

    if (value)
    {
        Draw::Rect::Fill(Vector2D(Position.x + 1, Position.y + 1), Vector2D(boxSize.x - 2, boxSize.y - 2), Colors(87, 121, 153, 255));
    }
}