#pragma once
#include "../vectors/vectors.h"

#include "../classes/classes.h"

class C_BaseEntity;

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
	static bool CalculateBoundingBox(C_BaseEntity* pEntity, BoundingBox& bbox, bool compute);
};