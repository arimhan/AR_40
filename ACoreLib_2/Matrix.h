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
	
	//단위행렬
	void Identity();

	//전치행렬
	AMatrix Transpose();

//카메라 행렬 만들기
	//외적을 통한 뷰 행렬 계산
	AMatrix ViewLookAt(AVector3& vPosition, AVector3& vTarget, AVector3& vUp);
	////내적을 통한 뷰 행렬 계산
	AMatrix	CreateViewLook(AVector3& vPosition, AVector3& vTarget, AVector3& vUp);
	//원근 투영 행렬 계산
	AMatrix	PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);


public:
	AMatrix();
};

