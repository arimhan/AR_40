#include "Vector2.h"
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
	x = v.x;  y = v.y;
}
AVector2 AVector2::operator+(const AVector2 & v)
{
	AVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
	//return AVector2(v.x + x, v.y + y);
}
AVector2 AVector2::operator-(const AVector2& v)
{
	AVector2 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	return ret;
	//return AVector2(x - v.x, y - v.y);
}
AVector2 AVector2::operator*(float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	return *this;
	//return AVector2(fValue * x, fValue * y);
}
AVector2 AVector2::operator /(float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	return *this;
	//return AVector2(fValue / x, fValue / y);
}
float AVector2::Length() //������ ��Ʈ������ �Ÿ����
{
	float ret = x * x + y * y;
	return sqrt(ret);
	//(float)sqrt(LengthSquared());
	//��Ʈ, a�� b�� ����
	//return sqrt(pow(v.x, 2) + pow(v.y, 2));
	//float AVector2::LengthSquared()
	//{
	//	return (x * x + y * y);
	//}
}
AVector2 AVector2::Normal() //�ڱ��ڽŸ� ����ȭ
{
	AVector2 ret;
	float normal = 1.0f / Length();
	return AVector2 (ret.x = x * normal,  ret.y = y * normal);
}
AVector2 AVector2::Normalization()
{
	float normal = 1.0f / Length();
	return AVector2( x *= normal, y *= normal);
}
AVector2 Normalization(AVector2& v) //�ٸ� ����� ����ȭ �߰� (v�� �޾� ����ȭ ó��)
{
	AVector2 ret;
	float normal = 1.0f / v.Length();
	return AVector2( ret.x = v.x* normal, ret.y = v.y*normal );
}
AVector2 AVector2::operator /(float fValue) 
{
	return AVector2(fValue / x, fValue / y);
}
bool AVector2::operator ==(const AVector2& v)  
// ���� �� - obj�� x,y���� ���� 0�� ������ (�Ǽ��ϱ� ������������ fabs�� 0.0001f �� ��) ���� ������ true ��ȯ
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
AVector2 AVector2::Normal() //�ڱ��ڽŸ� ����ȭ
{
	AVector2 ret;
	float length = 1.0f / Length();
	return AVector2(ret.x = x * length, ret.y = y * length);
}
AVector2 AVector2::Normalization()
{
	float length = 1.0f / Length();
	return AVector2(x = x * length, y = y * length);
}
AVector2 Normalization(AVector2& v) //�ٸ� ����� ����ȭ �߰� (v�� �޾� ����ȭ ó��)
{
	AVector2 ret;
	float length = 1.0f / v.Length();
	return AVector2(ret.x = v.x * length, ret.y = v.y * length);
}
float AVector2::Length() //������ ��Ʈ������ �Ÿ����
{
	float ret = x * x + y * y;
	return sqrt(ret);
}
