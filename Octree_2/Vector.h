#pragma once
#include <math.h>

struct Vector2
{
public:
	float x;
	float y;

	//연산자들 정의
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

	//내적
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

	//연산자들 정의
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

	Vector3 operator *(float s) //곱셈 실수 s값
	{
		Vector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;

		return ret;
	}

	Vector3 operator /(float fValue) //나눗셈은 실수 fValue로 받아서 계산 후 넘기기
	{
		Vector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;

		return ret;
	}

	Vector3 operator +=(Vector3 p)  // += 대입연산자. 왼쪽과 오른쪽 값을 더한 후 왼쪽에 대입
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


