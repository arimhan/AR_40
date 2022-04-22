#pragma once
#include "FbxImporter.h"
#include "Camera.h"

class AFbxObj : public AObject3D
{
public:
	ACamera*		m_pMainCamera;
	UINT			m_iShadowID = 0;
	TVector4		m_vShadowColor;

public:
	AFbxImporter*	m_pMeshImp;
	AFbxImporter*	m_pAnimImp;

	float			m_fDir = 1.0f;
	float			m_fTimer = 0.0f;
	float			m_fSpeed = 1.0f;
	ABoneWorld		m_matBoneArray;
	vector<AFbxObj> m_DrawList;
public:
	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool	Release() override;
	void			GenAABB() override;

	bool			RenderShadow(AShader* pShader);
	T::TMatrix		Interplate(AFbxImporter* pAnimImp, AFbxModel* pModel, float fTime);
};

