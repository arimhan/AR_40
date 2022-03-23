#pragma once
#include "Std.h"

class ACamera
{
public:
	//������Ʈ ������ ������ ī�޶� �ִ� �� ó�� �����ش�.
	//ī�޶� X������ 10 ������ -> ������Ʈ ������ X������ -10 ������

	AVector3		m_vLight;	//X
	AVector3		m_vUp;		//Y
	AVector3		m_vLook;	//Z

	//ī�޶� ����
	AVector3		m_vCamera;
	AVector3		m_vTarget;

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
