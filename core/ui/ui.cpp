#include "ui.h"


void UI::Setup()
{
    if (!UI::Toggled)
        return;

    if (UI::Toggled)
		Draw::Rect::Fill(Vector2D(WindowPosition.x, WindowPosition.y), Vector2D(WindowSize.x, WindowSize.y), Colors(0, 0, 0, 100));

    UI::Start();


    UI::End();
}

void UI::Start()
{
    auto& io = ImGui::GetIO();

    ImVec2 centeredPos = ImVec2((io.DisplaySize.x - Width) * 0.5f, (io.DisplaySize.y - Height) * 0.5f);

    if (!Initialize) {
        WindowPosition = Vector2D(centeredPos.x, centeredPos.y);
        WindowSize = Vector2D(Width, Height);
        Initialize = true;
    }

    ImGui::SetNextWindowPos(ImVec2(WindowPosition.x, WindowPosition.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(WindowSize.x, WindowSize.y), ImGuiCond_Always);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);

    ImGui::Begin("FrameWork", nullptr, WindowFlags);

    Vector2D pos = WindowPosition;
    Vector2D size = WindowSize;
    Vector2D mousePos(io.MousePos.x, io.MousePos.y);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::InvisibleButton("DragZone", ImVec2(size.x, size.y));

    bool dragActive = ImGui::IsItemActive();
    bool leftDown = io.MouseDown[0];

    if (dragActive && leftDown) {
        if (!IsDragging) {
            IsDragging = true;
            DragDelta = mousePos - pos;
        }
        pos = mousePos - DragDelta;
    }
    else {
        IsDragging = false;
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x + size.x > io.DisplaySize.x) pos.x = io.DisplaySize.x - size.x;
    if (pos.y + size.y > io.DisplaySize.y) pos.y = io.DisplaySize.y - size.y;

    ImGui::SetWindowPos(ImVec2(pos.x, pos.y));

    WindowPosition = pos;
}

void UI::End()
{
    ImGui::End();
}
