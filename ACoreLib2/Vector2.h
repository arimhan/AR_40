#pragma once
#include <iostream>
#include <math.h>

struct AFloat2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
struct AFloat4
{
	union
	{
		struct { float x, y,z,w; };
		float v[4];
	};
};
class AVector2 : public AFloat2
{
public:
	AVector2();
	AVector2(float x, float y);
	AVector2(const AVector2& v);
public:
	AVector2 operator + (const AVector2& v);
	AVector2 operator - (const AVector2& v);
	AVector2 operator * (float fValue);
	AVector2 operator / (float fValue);
	AVector2 operator += (const AVector2& v);
	AVector2 operator -= (const AVector2& v);
	bool operator == (const AVector2& v);
	bool operator != (const AVector2& v);
	// 정규화
	AVector2 Normalize();
	AVector2 Normal();
	friend AVector2 Normalize(AVector2& v);
	// 크기
	float Length();
	float Distance(AVector2& v);
};

class AVector4 : public AFloat4
{
public:
	AVector4() {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 0.0f;
	};
	AVector4(float x, float y, float z, float w) {
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}
	AVector4(const AVector4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
};