#pragma once
#include "Object3D.h"

//Face, �������� ����
struct AFace
{
	UINT			v0, v1, v2;	//vb index
	T::TVector3		vNormal;
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
	vector<float> m_fHeightList;	//���̰��� vector�������� �̰��� �����Ѵ�.
public:
	//ObJ�� Map�� ���̰��� ������ �Լ�, �������� �Լ������ �����Ѵ�.
	float GetHeight(float fPosX, float fPosZ);
	float GetHeightMap(int row, int col);
	//Linear Interpolation ���������Լ�
	float Lerp(float fStart, float fEnd, float fTangent); 
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

