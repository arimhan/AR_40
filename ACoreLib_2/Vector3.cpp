#include "Vector3.h"

AVector3::AVector3()
{
	x = y = z = 0.0f;
}
AVector3::AVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
AVector3::AVector3(const AVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
AVector3 AVector3::operator + (const AVector3& v)
{
	AVector3 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	ret.z = this->z + v.z;
	return ret;
}
AVector3 AVector3::operator - (const AVector3& v)
{
	AVector3 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	ret.z = this->z - v.z;
	return ret;
}
AVector3 AVector3::operator * (float fValue)
{
	AVector3 ret;
	ret.x = x * fValue;
	ret.y = y * fValue;
	ret.z = z * fValue;

	return ret;
}
AVector3 AVector3::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	this->z /= fValue;
	return *this;
}
void AVector3::operator += (const AVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
void AVector3::operator -= (const AVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
bool AVector3::operator == (const AVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return true;
			}
		}
	}
	return false;
}
bool AVector3::operator != (const AVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return false;
			}
		}
	}
	return true;
}

	//내적 외적 추가
float AVector3::operator | (AVector3 const& v)
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

AVector3 AVector3::operator ^ (AVector3 const& v)
{
	return AVector3((y*v.z - z*v.y) , (z * v.x - x * v.z), (x * v.y - y * v.x));
}


AVector3 AVector3::Normal()
{
	AVector3 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	ret.z = z * length;
	return ret;
}
AVector3 AVector3::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	z *= length;
	return *this;
}
AVector3 Normalize(AVector3& v)
{
	AVector3 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	ret.z = v.z * length;
	return ret;
}
// 크기
float AVector3::Length()
{
	float ret = x * x + y * y + z*z;
	return sqrt(ret);
}