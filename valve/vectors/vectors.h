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


class Matrix2x4_t {
public:
	float data[2][4];

	Matrix2x4_t() {
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 4; ++j)
				data[i][j] = 0.0f;
	}
};

class Matrix3x3_t {
public:
	float data[3][3];

	Matrix3x3_t() {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				data[i][j] = 0.0f;
	}
};

class Matrix3x4_t {
public:
	float data[3][4];

	Matrix3x4_t() {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 4; ++j)
				data[i][j] = 0.0f;
	}
};


class alignas(16) Transform_t
{
public:
	alignas(16) Vector3D m_pos;
	alignas(16) Vector4D m_rot;

	Matrix3x4_t ToMatrix3x4() const
	{
		return ToMatrix3x4(m_pos);
	}

	Matrix3x4_t ToMatrix3x4(const Vector3D& origin) const
	{
		Matrix3x4_t matrix{};

		const float x = m_rot.x;
		const float y = m_rot.y;
		const float z = m_rot.z;
		const float w = m_rot.w;

		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;

		const float xy = x * y;
		const float xz = x * z;
		const float yz = y * z;

		const float wx = w * x;
		const float wy = w * y;
		const float wz = w * z;

		matrix.data[0][0] = 1.f - 2.f * (yy + zz);
		matrix.data[0][1] = 2.f * (xy - wz);
		matrix.data[0][2] = 2.f * (xz + wy);

		matrix.data[1][0] = 2.f * (xy + wz);
		matrix.data[1][1] = 1.f - 2.f * (xx + zz);
		matrix.data[1][2] = 2.f * (yz - wx);

		matrix.data[2][0] = 2.f * (xz - wy);
		matrix.data[2][1] = 2.f * (yz + wx);
		matrix.data[2][2] = 1.f - 2.f * (xx + yy);

		matrix.data[0][3] = origin.x;
		matrix.data[1][3] = origin.y;
		matrix.data[2][3] = origin.z;

		return matrix;
	}
};