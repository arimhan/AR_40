#pragma once
#include "Vector2.h"
struct AFloat3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
class AVector3 : public AFloat3
{
public:
	AVector3();
	AVector3(float x, float y, float z);
	AVector3(const AVector3& v);
public:
	//������ ������
	AVector3 operator + (const AVector3& v);
	AVector3 operator - (const AVector3& v);
	AVector3 operator * (float fValue);
	AVector3 operator / (float fValue);
	bool operator == (const AVector3& v);
	bool operator != (const AVector3& v);

	//ũ��(�Ÿ�)
	float Length();
	//����ȭ
	AVector3 Normal();
	AVector3 Normalization();
	friend AVector3 Normalization(AVector3& v);
};

