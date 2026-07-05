#pragma once

#include "../renderer/renderer.h"

class UI
{
public:
	bool isToggled = false;
	bool isDragged = false;
	void paint();

private:
	void setup();
	void end();
	static inline ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
	static inline int width = 550, height = 500;
	static inline Vector2D windowPosition, windowSize, dragDelta;
	static inline bool initialize = false;
};

inline UI ui;