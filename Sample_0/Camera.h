#pragma once
//#include "Matrix.h"
#include "Std.h"

class ACamera
{
public:
	//������Ʈ ������ ������ ī�޶� �ִ� �� ó�� �����ش�.
	//ī�޶� X������ 10 ������ -> ������Ʈ ������ X������ -10 ������

	//ī�޶� ����
	AVector3		m_vCamera;
	AVector3		m_vTarget;
	AVector3		m_vUp;

	//���
	AMatrix			m_matWorld;
	AMatrix			m_matView;
	AMatrix			m_matProj;

public:
	virtual bool Init();
	virtual bool Frame();
public:
	ACamera();
	virtual ~ACamera();
};

class Camera
{
};

