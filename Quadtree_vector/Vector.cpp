#include "Vector.h"
#include <cmath>
//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=pjw4687&logNo=220674917458
AVector2::AVector2()
{
	x = y = 0;
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

	/*this->x += v.x;
	this->y += v.y;
	return *this;*/
}
AVector2 AVector2::operator-(AVector2 const &v)
{
	return AVector2(x - v.x, y - v.y);
/*
	this->x -= v.x;
	this->y -= v.y;
	return *this;*/
}
AVector2 AVector2::operator*(float const &fs)
{
	/*
	s* this->x;
	s* this->y;*/

	return AVector2(fs * x, fs * y);
}
float AVector2::LengthSquared() //
{
	return (x * x + y * y);
}
float AVector2::Length() //Á¦°ö¿¡ ·çÆ®¾º¿ö¼­ °Å¸®°è»ê
{
	return (float)sqrt(LengthSquared());
	//·çÆ®, a¿¡ b½Â Á¦°ö
	//return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
AVector2 AVector2::Normalization()
{
	float normal = 1.0f/Length();
	return AVector2(x * normal, y * normal);
	/*this->x = x / normal;
	this->y = y / normal;

	return AVector2(this->x = x/normal, this->y = y/normal);*/
	/*
	float Len = Length(v);
	return AVector2(v.x / Len, v.y / Len);*/
}