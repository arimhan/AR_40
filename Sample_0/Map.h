#pragma once
#include "Object3D.h"

//Face, 정점등을 관리
struct AFace
{
	UINT		v0, v1, v2;	//vb index
	AVector3	vNormal;
};
//struct AVertexFace
//{
//	vector<UINT> viFaceList;
//};

class AMap : public AObject3D
{
public:
	vector<AFace> m_vFaceList;
	//vector<AVertexFace> m_vVertexFaceList;

	UINT	m_iNumCols = 0;
	UINT	m_iNumRows = 0;
	UINT	m_iNumVertices = 0;
	UINT	m_iNumCellCols = 0;
	UINT	m_iNumCellRows = 0;
	UINT	m_iNumFaces = 0;

	float	m_iCellDistance = 1.0f;
	vector<float> m_fHeightList;	//높이값 리스트
public:
	virtual bool CreateHeightMap(const TCHAR* strHeightMapTex);
	virtual bool CreateMap(UINT width, UINT height, float fDistance);
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	virtual bool Frame() override;
public:
	AMap();
	virtual ~AMap();
};

