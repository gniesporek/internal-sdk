#pragma once

#include "../vectors/vectors.h"

class BoundingBox {
public:
	int x, y, w, h;
	BoundingBox() = default;
	BoundingBox(const int x,const int y,const int w,const int h) : x(x), y(y), w(w), h(h) {}
};

class Math {
public:
	static int CalculateSegments(float radius);
	static bool WorldToScreen(const Vector3D& worldPos, Vector2D& screenPos);
};