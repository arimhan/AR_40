#pragma once
//#include "Matrix.h"
#include "Std.h"

class ACamera
{
public:
	//오브젝트 정점을 움직여 카메라가 있는 것 처럼 보여준다.
	//카메라를 X축으로 10 움직임 -> 오브젝트 정점을 X축으로 -10 움직임

	//카메라 벡터
	AVector3		m_vCamera;
	AVector3		m_vTarget;
	AVector3		m_vUp;

	//행렬
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

