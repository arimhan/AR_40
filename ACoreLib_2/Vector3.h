#pragma once
#include "Vector2.h"
namespace AMath
{
	struct AFloat3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};
	class AVector3 : public AFloat3
	{
	public:
		AVector3();
		AVector3(float x, float y, float z);
		AVector3(const AVector3& v);
	public:
		AVector3 operator + (const AVector3& v);
		AVector3 operator - (const AVector3& v);
		AVector3 operator * (float fValue);
		AVector3 operator / (float fValue);
		void operator += (const AVector3& v);
		void operator -= (const AVector3& v);
		bool operator == (const AVector3& v);
		bool operator != (const AVector3& v);

		//내적 외적 추가
		float operator | (AVector3 const &v);
		AVector3 operator ^ (AVector3 const& v);

		// 정규화
		AVector3 Normalize();
		AVector3 Normal();
		friend AVector3 Normalize(AVector3& v);

		// 크기
		float Length();
	};

}