#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"
#include "Map.h"
#include "SkyObj.h"
#include "BoxObj.h"
#include "Quadtree.h"

#define MAX_NUM_OBJECTS 100

class ASample : public ACore
{
	ACamera				m_Camera;
	ACamera				m_CameraTopView;
	AMap				m_MapObj;
	ABoxObj				m_PlayerObj_1;
	vector<AMapObj*>	m_pObjList;
	ABoxObj*			m_pBoxObj;
	AQuadtree			m_Quadtree;
	ASkyObj				m_SkyObj;
public:
	T::TVector3			m_vIntersection;
	vector<T::TVector3>	m_vIntersectionList;
	//bool GetIntersection(T::TVector3 vStart, T::TVector3 vEnd,
		//T::TVector3 v0, T::TVector3 v1, T::TVector3 v2, T::TVector3 vNormal);
	//bool PointInPolygon(T::TVector3 vert, T::TVector3 faceNormal,
		//T::TVector3 v0, T::TVector3 v1, T::TVector3 v2);
public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;

	void			CreateMapObject();
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	bool			MiniMapRender();

	ASample();
	virtual ~ASample();
};