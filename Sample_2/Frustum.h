#pragma once
#include "Std.h"
#include "BoxObj.h"


class AFrustum : public ABoxObj
{
public:
	T::TPlane		m_Plane[6];
	T::TVector3		m_vFrustum[8];
public:
	bool			Init();
	void			CreateFrustum(T::TMatrix& matView, T::TMatrix& matProj);

	//C언어의 논리자료형, 정수형 4Byte, 초기값 쓰레기
	BOOL			ClassifyPoint(T::TVector3* v);
	BOOL			ClassifySphere(ASphere* v);
	BOOL			ClassifyOBB(ABox* v);
public:
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	bool			PostRender();
};

