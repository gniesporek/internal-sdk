#pragma once

#include "ui.h"

#include "controls/controls.h"
#include "controls/variables.h"

class Widgets
{
public:
	static void DrawForm(Vector2D position, Vector2D size, const char* title);
	static void Dropdown(Vector2D position, const std::vector<std::string>& options, int& selectedSubtab);
	static void SubTab(Vector2D Position, const std::string subTabName, int height);
private:
	static inline int selectedSubtab = 0;

};