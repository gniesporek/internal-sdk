#pragma once

#include "ui.h"


class Widgets
{
public:
	static void DrawForm(Vector2D position, Vector2D size, const char* title);
	static void Dropdown(Vector2D position, const std::vector<std::string>& options, int& selectedSubtab);
	static void SubTab(Vector2D Position, const std::string subTabName, int height);
private:

};