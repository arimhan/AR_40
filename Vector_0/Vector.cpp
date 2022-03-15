#include "Vector.h"


AVector2::AVector2()
{
	x = y = 0.0f;
}
AVector2::AVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
AVector2::AVector2(const AVector2& v)
{
	x = v.x;
	y = v.y;
}
AVector2 AVector2::operator + (const AVector2& v)
{
	AVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
}
AVector2 AVector2::operator - (const AVector2& v)
{
	AVector2 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	return ret;
}

AVector2 AVector2::operator * (float fValue)
{
	AVector2 ret;
	ret.x = this->x * fValue;
	ret.y = this->y * fValue;
	return ret;
}
AVector2 AVector2::operator / (float fValue)
{
	AVector2 ret;
	ret.x = this->x / fValue;
	ret.y = this->y / fValue;
	return ret;
}
AVector2 AVector2::operator += (const AVector2& v)
{
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	return *this;
}
AVector2 AVector2::operator -= (const AVector2& v)
{
	this->x = this->x - v.x;
	this->y = this->y - v.y;
	return *this;
}
bool AVector2::operator == (const AVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return true;
		}
	}
	return false;
}
bool AVector2::operator != (const AVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return false;
		}
	}
	return true;
}

AVector2 AVector2::Normal()
{
	AVector2 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	return ret;
}
AVector2 AVector2::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	return *this;
}
AVector2 Normalize(AVector2& v)
{
	AVector2 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	return ret;
}
// 크기
float AVector2::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}
// 두벡터의 거리 반환
float AVector2::Distance(AVector2& v)
{
	float fDist = (*this - v).Length();
	return fDist;
}
//벡터 내적
float AVector3::operator |(AVector3 const& v0)
{
	//(ax*bx)+(ay*by)+(az*bz) 내적공식
	return x * v0.x + y * v0.y + z * v0.z;
}
//벡터 외적
AVector3 AVector3::operator ^(AVector3 const& v0)
{
	//(Ay*Bz - Az*By), (Az*Bx - Ax*Bz), (Ax*By - Ay*Bz) 외적공식
	return AVector3((y * v0.z - z * v0.y), (z * v0.x - x * v0.z), (x * v0.y - y * v0.x));
}

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
	this->x *= fValue;
	this->y *= fValue;
	this->z *= fValue;
	return *this;
}
AVector3 AVector3::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	this->z /= fValue;
	return *this;
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
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}