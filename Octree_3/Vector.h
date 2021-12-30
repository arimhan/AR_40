#pragma once
#include <math.h>

class AVector3
{
public:
	float x;
	float y;
	float z;

	//�����ڵ� ����
	AVector3 operator +(AVector3 p)
	{
		AVector3 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		ret.z = z + p.z;

		return ret;
	}
	AVector3 operator -(AVector3 p)
	{
		AVector3 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		ret.z = z - p.z;

		return ret;
	}
	AVector3 operator *(float s) //���� �Ǽ� s��
	{
		AVector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;

		return ret;
	}
	AVector3 operator /(float fValue) //�������� �Ǽ� fValue�� �޾Ƽ� ��� �� �ѱ��
	{
		AVector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;

		return ret;
	}
	AVector3 operator +=(AVector3 p)  // += ���Կ�����. ���ʰ� ������ ���� ���� �� ���ʿ� ����
	{
		AVector3 ret;
		x += p.x;
		y += p.y;
		z += p.z;

		return *this;
	}
	float operator | (AVector3 p);
	float DotProduct(AVector3 a, AVector3 b);
	float Length();
	AVector3 Normalize();
	float ProjectionPoint(AVector3 q1, AVector3 q2, AVector3 v);

	AVector3() {}
	AVector3(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


