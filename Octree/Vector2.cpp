#include "Vector2.h"
#include <cmath>
//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=pjw4687&logNo=220674917458
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
	x = v.x; y = v.y;
}
AVector2 AVector2::operator+(AVector2 const& v)
{
	return AVector2(v.x + x, v.y + y);
}
AVector2 AVector2::operator-(const AVector2& v)
{
	return AVector2(x - v.x, y - v.y);
}
AVector2 AVector2::operator*(float fValue)
{
	return AVector2(fValue * x, fValue * y);
}
float AVector2::LengthSquared()
{
	return (x * x + y * y);
}
float AVector2::Length() //제곱에 루트씌워서 거리계산
{
	return (float)sqrt(LengthSquared());
	//루트, a에 b승 제곱
	//return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
AVector2 AVector2::Normal() //자기자신만 정규화
{
	AVector2 ret;
	float normal = 1.0f / Length();
	ret.x = x * normal;
	ret.y = y * normal;
	return ret;
}
AVector2 AVector2::Normalization()
{
	AVector2 ret;
	float normal = 1.0f / Length();
	return AVector2(x = x * Length(), y = y * Length());
}
AVector2 Normalization(AVector2& v) //다른 기능의 정규화 추가 (v를 받아 정규화 처리)
{
	AVector2 ret;
	float normal = 1.0f / v.Length();
	ret.x = v.x * v.Length();
	ret.y = v.y * v.Length(); 
	return ret;
}
AVector2 AVector2::operator /(float fValue) 
{
	return AVector2(fValue / x, fValue / y);
}
bool AVector2::operator ==(const AVector2& v)  
// 기존 값 - obj의 x,y값의 차가 0에 가까우면 (실수니까 오차범위땜시 fabs와 0.0001f 로 비교) 같기 때문에 true 반환
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
bool AVector2::operator !=(const AVector2& v) 
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