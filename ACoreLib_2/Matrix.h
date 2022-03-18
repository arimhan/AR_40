#pragma once
#include "Vector3.h"

//ī�޶�� ������ �������� ������ ������Ʈ ������ ī�޶� �����̰� ���� ���ݴ� ���(�����)�� ���ϸ�
//ī�޶� �����̴� �� ���� ������� ����Ѵ�.

struct float4x4 // 4x4 ��� ����
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
	
	//ȸ�����
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);

	//���� �� �������
	void Translation(const AVector3 &v);
	void Translation(float x, float y, float z);
	void Scale(const AVector3& v);
	void Scale(float x, float y, float z);
	
	//�������
	void Identity();

	//��ġ���
	AMatrix Transpose();

//ī�޶� ��� �����
	//������ ���� �� ��� ���
	AMatrix ViewLookAt(AVector3& vPosition, AVector3& vTarget, AVector3& vUp);
	////������ ���� �� ��� ���
	AMatrix	CreateViewLook(AVector3& vPosition, AVector3& vTarget, AVector3& vUp);
	//���� ���� ��� ���
	AMatrix	PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);


public:
	AMatrix();
};

