#include "widgets.h"

void Widgets::DrawForm(Vector2D position, Vector2D size, const char* title)
{
    Colors colors[] = { Colors(0, 0, 0, 255),  Colors(60, 60, 60, 255),Colors(40, 40, 40, 255), Colors(60, 60, 60, 255) };

    for (int i = 0; i < 4; i++)
    {
        Draw::Rect::Draw(Vector2D(position.x + i, position.y + i), Vector2D(size.x - 2 * i, size.y - 2 * i), colors[i]);
        Draw::Rect::Fill(Vector2D(position.x + 4, position.y + 4), Vector2D(size.x - 8, size.y - 8), Colors(20, 20, 20, 255));
    }

	Draw::Line::Draw(Vector2D(position.x + 4, position.y + 23), Vector2D(position.x + size.x - 4, position.y + 23), Colors(60, 60, 60, 255), 1.0f);

	Draw::Text::Draw(ImGui::GetFont(), Vector2D(position.x + 10, position.y + 6), title, Colors(255, 255, 255, 255), false);


	Draw::Text::Draw(ImGui::GetFont(), Vector2D(position.x + size.x - 10 - Draw::Text::GetTextWidth(ImGui::GetFont(), __DATE__), position.y + 6), __DATE__, Colors(255, 255, 255, 255), false);

	Widgets::Dropdown(Vector2D(position.x + 20, position.y + 50), { "assistance","visuals","miscellaneous"}, selectedSubtab);

    switch (selectedSubtab)
    {
    case 0:
        Widgets::SubTab(Vector2D(position.x + 188, position.y + 50), "assistance configuration", 258);

        break;

    case 1:
        Widgets::SubTab(Vector2D(position.x + 188, position.y + 50), "visuals configuration", 258);

		Controls::CheckBox::Draw(Vector2D(position.x + 176, position.y + 59), "enable", Variables::Visuals::Enable);
		Controls::CheckBox::Draw(Vector2D(position.x + 176, position.y + 74), "bounding box", Variables::Visuals::BoundingBox);

        break;

    case 2:
        Widgets::SubTab(Vector2D(position.x + 188, position.y + 50), "miscellaneous configuration", 258);

        break;

    default:
        break;
    }
}

void Widgets::Dropdown(Vector2D Position, const std::vector<std::string>& options, int& selectedSubtab)
{
    int optionHeight = 21;
    int spacing = 3;
    int x = Position.x;

    int rectX = x - 9;
    int rectW = 150;

    int startY = Position.y - 19;
    int optionY = startY + 1;

    Draw::Rect::Draw(Vector2D(rectX, startY), Vector2D(rectW, 258), Colors(40, 40, 40, 255));

    for (size_t i = 0; i < options.size(); ++i)
    {
        const std::string& option = options[i];

        bool isSelected = (selectedSubtab == (int)i);

        Colors bgColor = isSelected ? Colors(65, 65, 65, 100) : Colors(40, 40, 40, 100);
        Draw::Rect::Fill(Vector2D(rectX + 1, optionY), Vector2D(rectW - 2, optionHeight), bgColor);

        ImVec2 mousePos = ImGui::GetIO().MousePos;

        bool hovered =  mousePos.x >= rectX && mousePos.x <= rectX + rectW && mousePos.y >= optionY && mousePos.y <= optionY + optionHeight;

        Colors textColor = isSelected ? Colors(255, 255, 255, 255) : (hovered ? Colors(200, 200, 200, 255) : Colors(160, 160, 160, 150));

        Draw::Text::Draw(ImGui::GetFont(), Vector2D(x - 2, optionY + 3), option.c_str(), textColor, false);

        if (mousePos.x >= rectX && mousePos.x <= rectX + rectW && mousePos.y >= optionY && mousePos.y <= optionY + optionHeight && ImGui::IsMouseClicked(0))
        {
            selectedSubtab = (int)i;
        }

        if (isSelected)
        {
            Draw::Line::Draw(Vector2D(rectX, optionY), Vector2D(rectX, optionY + optionHeight), Colors(87, 121, 153, 150), 1.0f);
        }

        optionY += optionHeight + spacing;
    }
}

void Widgets::SubTab(Vector2D Position, const std::string subTabName, int height)
{
    Draw::Rect::Draw(Vector2D(Position.x - 20, Position.y - 19), Vector2D(221, height), Colors(40, 40, 40, 255));

    Draw::Rect::Draw(Vector2D(Position.x - 20, Position.y - 19), Vector2D(221, 21), Colors(40, 40, 40, 255));

    Draw::Rect::Fill(Vector2D(Position.x - 19, Position.y - 18), Vector2D(219, 19), Colors(30, 30, 30, 255));

    Draw::Text::Draw(ImGui::GetFont(), Vector2D(Position.x - 13, Position.y - 16), subTabName.c_str(), Colors(255, 255, 255, 255), false);
}