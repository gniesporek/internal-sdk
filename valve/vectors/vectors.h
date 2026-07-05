#pragma once

#include <cstdlib>

class Vector2D {
public:
	float x, y;

	Vector2D() : x(0), y(0) {};
	Vector2D(float x, float y) : x(x), y(y) {};

	Vector2D operator+(const Vector2D& v) const {
		return Vector2D(x + v.x, y + v.y);
	}
	Vector2D operator-(const Vector2D& v) const {
		return Vector2D(x - v.x, y - v.y);
	}
	Vector2D operator*(float scalar) const {
		return Vector2D(x * scalar, y * scalar);
	}
	Vector2D operator/(float scalar) const {
		return Vector2D(x / scalar, y / scalar);
	}

	float Dot(const Vector2D& v) const {
		return x * v.x + y * v.y;
	}
	float Length() const {
		return sqrtf(x * x + y * y);
	}
	Vector2D Normalize() const {
		float len = Length();
		if (len == 0) return Vector2D(0, 0);
		return Vector2D(x / len, y / len);
	}

	float DistanceTo(const Vector2D& v) const {
		return (*this - v).Length();
	}
};

class Vector3D {
public:
	float x, y, z;
	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};

	Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
	Vector3D operator*(float scalar) const {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}
	Vector3D operator/(float scalar) const {
		return Vector3D(x / scalar, y / scalar, z / scalar);
	}
};

class Vector4D {
public:
	float x, y, z, w;
	Vector4D() : x(0), y(0), z(0), w(0) {};
	Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	Vector4D operator+(const Vector4D& v) const {
		return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	Vector4D operator-(const Vector4D& v) const {
		return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	Vector4D operator*(float scalar) const {
		return Vector4D(x * scalar, y * scalar, z * scalar, w * scalar);
	}
	Vector4D operator/(float scalar) const {
		return Vector4D(x / scalar, y / scalar, z / scalar, w / scalar);
	}
};

template <typename T>
class CUtlVector {
public:
	auto at(int i) const { return data[i]; }
	auto atPtr(int i) const { return data + i; }

	// C++ STL Iterators
	auto begin() const { return data; }
	auto end() const { return data + size; }

	int size;
	char pad0[0x4];
	T* data;
	char pad1[0x8];
};