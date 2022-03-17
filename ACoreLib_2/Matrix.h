#pragma once
#include "Vector3.h"

//카메라는 실제로 존재하지 않으며 오브젝트 정점에 카메라가 움직이고 싶은 정반대 행렬(역행렬)을 곱하면
//카메라가 움직이는 것 같은 결과물을 출력한다.

struct float4x4 // 4x4 행렬 세팅
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class AMatrix : public float4x4
{
public:

	AMatrix operator * (AMatrix const& Matrix);
	
	//회전행렬
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);

	//변형 및 신축행렬
	void Translation(const AVector3 &v);
	void Translation(float x, float y, float z);
	void Scale(const AVector3& v);
	void Scale(float x, float y, float z);
	
	//단일행렬
	void Identity()
	{
		//단일행렬 세팅
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
		//4x4 0으로 세팅 후, 대각선 라인 성분 1.0f으로 변경
		_11 = _22 = _33 = _44 = 1.0f;
	}

	//전치행렬
	AMatrix Transpose();


public:
	AMatrix();
};

