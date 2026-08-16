#pragma once
#include "../widgets.h"

#include "../input_manager.h"

class Controls {
public:

	class CheckBox {
	public:
		static void Draw(Vector2D Position, const std::string& label, bool& value);
	};

};