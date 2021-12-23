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

//¿¬»êÀÚ ÀçÁ¤ÀÇ
	AVector2 operator+(const AVector2  &v);
	//º¤ÅÍ »¬¼À, ½ºÄ®¶ó °ö¼À
	AVector2 operator - (AVector2 const &v0);
	AVector2 operator *(float const& fs);

	//Á¤±ÔÈ­ , Å©±â(°Å¸®)
	float LengthSquared();
	float Length();
	AVector2 Normalization();


};

