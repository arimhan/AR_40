#pragma once
#include <math.h>

struct Vector2
{
public:
	float x;
	float y;

	//�����ڵ� ����
	Vector2 operator +(Vector2 p)
	{
		Vector2 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		return ret;
	}

	Vector2 operator -(Vector2 p)
	{
		Vector2 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		return ret;
	}

	Vector2 operator *(float s) 
	{
		Vector2 ret;
		ret.x = x * s;
		ret.y = y * s;
		return ret;
	}

	Vector2 operator /(float fValue) 
	{
		Vector2 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		return ret;
	}

	Vector2 operator +=(Vector2 p)  
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	//����
	float operator | (Vector2 p);
	float DotProduct(Vector2 a, Vector2 b);
	float ProjectionPoint(Vector2 a, Vector2 q2, Vector2 p);
	Vector2 Normalize();
	float Length();


	Vector2() {}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};



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

	Vector3() {}
	Vector3(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


