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
	x = v.x; y = v.y; z = v.z;
}
AVector3 AVector3::operator+(const AVector3& v)
{
	return AVector3(v.x + x, v.y + y, v.z + z);
}
AVector3 AVector3::operator-(const AVector3& v)
{
	return AVector3(x - v.x, y - v.y, z - v.x);
}
AVector3 AVector3::operator*(float fValue)
{
	return AVector3(fValue * x, fValue * y, fValue * z);
}
AVector3 AVector3::operator /(float fValue)
{
	return AVector3(fValue / x, fValue / y, fValue / z);
}
bool AVector3::operator ==(const AVector3& v)
// 기존 값 - obj의 x,y값의 차가 0에 가까우면 (실수니까 오차범위땜시 fabs와 0.0001f 로 비교) 같기 때문에 true 반환
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
bool AVector3::operator !=(const AVector3& v)
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
AVector3 AVector3::Normal() //자기자신만 정규화
{
	AVector3 ret;
	float length = 1.0f / Length();
	return AVector3(ret.x = x * length, ret.y = y * length, ret.z * length);
}
AVector3 AVector3::Normalization()
{
	float length = 1.0f / Length();
	return AVector3(x *= length, y *= length, z *= length);
}
AVector3 Normalization(AVector3& v) //다른 기능의 정규화 추가 (v를 받아 정규화 처리)
{
	AVector3 ret;
	float length = 1.0f / v.Length();
	return AVector3(ret.x = v.x * length, ret.y = v.y * length, ret.z = v.z * length);
}
float AVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}

