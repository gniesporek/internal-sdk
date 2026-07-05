#include "ui.h"


void UI::paint()
{
    if (!UI::isToggled)
        return;


    if (UI::isToggled)
		drawingSystem.rect.fill(Vector2D(0, 0), Vector2D(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), Colors(0, 0, 0, 25));


    UI::setup();


    UI::end();
}

void UI::setup()
{
    auto& io = ImGui::GetIO();

    ImVec2 centeredPos = ImVec2((io.DisplaySize.x - width) * 0.5f, (io.DisplaySize.y - height) * 0.5f);

    if (!initialize) {
        windowPosition = Vector2D(centeredPos.x, centeredPos.y);
        windowSize = Vector2D(width, height);
        initialize = true;
    }

    ImGui::SetNextWindowPos(ImVec2(windowPosition.x, windowPosition.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y), ImGuiCond_Always);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);

    ImGui::Begin("FrameWork", nullptr, windowFlags);

    Vector2D pos = windowPosition;
    Vector2D size = windowSize;
    Vector2D mousePos(io.MousePos.x, io.MousePos.y);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::InvisibleButton("DragZone", ImVec2(size.x, size.y));

    bool dragActive = ImGui::IsItemActive();
    bool leftDown = io.MouseDown[0];

    if (dragActive && leftDown) {
        if (!isDragged) {
            isDragged = true;
            dragDelta = mousePos - pos;
        }
        pos = mousePos - dragDelta;
    }
    else {
        isDragged = false;
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x + size.x > io.DisplaySize.x) pos.x = io.DisplaySize.x - size.x;
    if (pos.y + size.y > io.DisplaySize.y) pos.y = io.DisplaySize.y - size.y;

    ImGui::SetWindowPos(ImVec2(pos.x, pos.y));

    windowPosition = pos;
}

void UI::end()
{
    ImGui::End();
}
