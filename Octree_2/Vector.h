#pragma once
#include <math.h>

class Vector3
{
public:
	float x;
	float y;
	float z;

	//�����ڵ� ����
	Vector3 operator +(Vector3 p)
	{
		Vector3 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		ret.z = z + p.z;

		return ret;
	}
	Vector3 operator -(Vector3 p)
	{
		Vector3 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		ret.z = z - p.z;

		return ret;
	}
	Vector3 operator *(float s) //���� �Ǽ� s��
	{
		Vector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;

		return ret;
	}
	Vector3 operator /(float fValue) //�������� �Ǽ� fValue�� �޾Ƽ� ��� �� �ѱ��
	{
		Vector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;

		return ret;
	}
	Vector3 operator +=(Vector3 p)  // += ���Կ�����. ���ʰ� ������ ���� ���� �� ���ʿ� ����
	{
		Vector3 ret;
		x += p.x;
		y += p.y;
		z += p.z;

		return *this;
	}
	//����
	float operator | (Vector3 p);
	float DotProduct(Vector3 a, Vector3 b, Vector3 c);
	float ProjectionPoint(Vector3 a, Vector3 q2, Vector3 p);
	Vector3 Normalize();
	float Length();

	Vector3() {}
	Vector3(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


