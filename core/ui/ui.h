#pragma once

#include "../renderer/renderer.h"

class UI {
public:
	static void Setup();
	static inline bool Toggled = true, IsDragging = false;
private:
	static void Start();
	static void End();
	static inline ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	static inline int Width = 500, Height = 500;
	static inline Vector2D WindowPosition, WindowSize, DragDelta;
	static inline bool Initialize = false;
};