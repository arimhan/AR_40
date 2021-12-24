#pragma once
#include <math.h>
struct AFloat2
{
	union
	{
		struct { float x, y; };
		//union에 float x,y로 해놓으니 마지막에 넣은 y값으로 바뀌지^^..구조체로 감싸줘라
		float v[2];
		//Pos
	};
};
class AVector2 : public AFloat2
{
public:
	AVector2();
	AVector2(float x, float y);
	AVector2(const AVector2& v);
public:
	//연산자 재정의
	AVector2 operator+(const AVector2& v);
	AVector2 operator - (const AVector2& v0);
	AVector2 operator *(float fValue);
	AVector2 operator /(float fValue);
	bool operator ==(const AVector2& v);
	bool operator !=(const AVector2& v);

	//크기(거리)
	float LengthSquared();
	float Length();
	//정규화
	AVector2 Normal();
	AVector2 Normalization();
	friend AVector2 Normalization(AVector2& v);
};

