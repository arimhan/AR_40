#include "Vector.h"
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
AVector2::AVector2(const AVector2 &v)
{
	x = v.x; y = v.y;
}
AVector2 AVector2::operator+(AVector2 const &v)
{
	return AVector2(v.x + x, v.y + y);
}
AVector2 AVector2::operator-(const AVector2 &v)
{
	return AVector2(x - v.x, y - v.y);
}
AVector2 AVector2::operator*(const float &fs)
{
	return AVector2(fs * x, fs * y);
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
AVector2 AVector2::Normalization()
{
	AVector2 ret;
	float normal = 1.0f / Length();
	return AVector2(x = x * Length(), y = y * Length());
}
AVector2 AVector2::Normalization(const AVector2 &v) //다른 기능의 정규화 추가 (v를 받아 정규화 처리)
{
	AVector2 ret;
	float normal = 1.0f/Length();
	ret.x = v.x * Length();
	ret.y = v.y * Length();
	return ret;
}
AVector2 AVector2::Normal() //자기자신만 정규화
{
	AVector2 ret;
	float normal = 1.0f / Length();
	x *= normal;
	y *= normal;
	return ret;
}