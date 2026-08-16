#pragma once

#include <cstdlib>

#include "../../core/utils/utils.h"

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

	bool IsZero() const {
		return x == 0 && y == 0 && z == 0;
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

template <typename T>
struct RepeatedPtrField_t
{
public:

	struct Rep_t
	{
		int nAllocatedSize;
		T* tElements[(2147483647 - 2 * sizeof(int)) / sizeof(void*)];
	};

	void* pArena;
	int nCurrentSize;
	int nTotalSize;
	Rep_t* pRep;

	template <typename T>
	T* Add(T* element)
	{
		typedef T* (__fastcall* AddElementFunc_t)(void*, T*);
		static AddElementFunc_t AddElementFunc = (AddElementFunc_t)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 8B FA 48 8B 49 ? 48 85 C9 74 ? 8B 01");
		return AddElementFunc(this, element);
	}
};

class TimeStamp
{
public:
	int tick{};
	float fraction{};

	TimeStamp(float t)
	{
		auto temp = std::fmodf(t, 0.015625f);
		fraction = temp * 64;
		tick = TIME_TO_TICKS(t - temp);
		Normalize();
	}

	void Normalize()
	{
		if (fraction < 1.f)
		{
			if (fraction <= 0.f)
				fraction = 0.f;
		}
		else
		{
			tick++;
			fraction = 0.f;
		}
	}

	float ToTime()
	{
		return static_cast<float>(tick) * 0.015625f + fraction * 0.015625;
	}
};