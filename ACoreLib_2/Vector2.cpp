#include "Vector2.h"

namespace AMath
{
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
 }