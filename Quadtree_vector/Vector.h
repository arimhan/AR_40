#pragma once
struct AFloat2
{
	union
	{
		float x;
		float y;
		float v[2];
	};	
};
class AVector2 : public AFloat2
{
public:
	AVector2();
	AVector2(float x, float y);
	AVector2(const AVector2  &v);

public:

//������ ������
	AVector2 operator+(const AVector2  &v);
	//���� ����, ��Į�� ����
	AVector2 operator - (AVector2 const &v0);
	AVector2 operator *(float const& fs);

	//����ȭ , ũ��(�Ÿ�)
	float LengthSquared();
	float Length();
	AVector2 Normalization();


};

