#pragma once
#include "Std.h"
#include "BoxObj.h"


class AFrustum : public ABoxObj
{
public:
	A::APlane		m_Plane[6];
	A::AVector3		m_vFrustum[8];
public:
	bool			Init();
	void			CreateFrustum(A::AMatrix& matView, A::AMatrix& matProj);

	//C����� ���ڷ���, ������ 4Byte, �ʱⰪ ������
	BOOL			ClassifyPoint(A::AVector3* v);
	BOOL			ClassifySphere(ASphere* v);
	BOOL			ClassifyOBB(ABox* v);
public:
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	bool			PostRender();
};

