#pragma once
struct AFloat2
{
	union
	{
		struct { float x, y; };
		//union�� float x,y�� �س����� �������� ���� y������ �ٲ���^^..����ü�� �������
		float v[2];
		//Pos
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
	AVector2 operator - (const AVector2  &v0);
	AVector2 operator *(const float & fs);

	//����ȭ , ũ��(�Ÿ�)
	float LengthSquared();
	float Length();
	AVector2 Normalization();
	AVector2 Normalization(const AVector2& v);
	AVector2 Normal();


};

