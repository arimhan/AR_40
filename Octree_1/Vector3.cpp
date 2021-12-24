#include "Vector3.h"
AVector3::AVector3()
{
	x = y = 0.0f;
}
AVector3::AVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
}
AVector3::AVector3(const AVector3& v)
{
	x = v.x; y = v.y;
}
AVector3 AVector3::operator+(const AVector3& v)
{
	return AVector3(v.x + x, v.y + y, v.z + x);
}
AVector3 AVector3::operator-(const AVector3& v)
{
	return AVector3(x - v.x, y - v.y, z - v.x);
}
AVector3 AVector3::operator*(float fValue)
{
	return AVector3(fValue * x, fValue * y, fValue * z);
}
float AVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}
AVector3 AVector3::Normal() //�ڱ��ڽŸ� ����ȭ
{
	AVector3 ret;
	float normal = 1.0f / Length();
	return AVector3(ret.x = x * normal, ret.y = y * normal, ret.z * normal);
}
AVector3 AVector3::Normalization()
{
	float normal = 1.0f / Length();
	return AVector3(x *= normal, y *= normal, z *= normal);
}
AVector3 Normalization(AVector3& v) //�ٸ� ����� ����ȭ �߰� (v�� �޾� ����ȭ ó��)
{
	AVector3 ret;
	float normal = 1.0f / v.Length();
	return AVector3(ret.x = v.x * normal, ret.y = v.y * normal, ret.z = v.z * normal);
}
AVector3 AVector3::operator /(float fValue)
{
	return AVector3(fValue / x, fValue / y, fValue / z);
}
bool AVector3::operator ==(const AVector3& v)
// ���� �� - obj�� x,y���� ���� 0�� ������ (�Ǽ��ϱ� ������������ fabs�� 0.0001f �� ��) ���� ������ true ��ȯ
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