#pragma once
#include "Object3D.h"
#include <fbxsdk.h>

struct ATrack
{
	UINT	iFrame;
	TMatrix matTrack;
};

class AFbxObject : public AObject3D
{
public:
	//Animation 추가
	TMatrix		m_matLocal;
	TMatrix		m_matAnim;
	//int			m_iIndex = -1;

	FbxNode*	m_pFbxParent	= nullptr;
	FbxNode*	m_pFbxNode		= nullptr;
	AFbxObject*	m_pParentObj	= nullptr;
	wstring		m_szTexFileName;

	//SubMaterial
	vector<wstring>			m_szTexFileList;
	using ASubVertex = vector<AVertex>;
	vector<ASubVertex>		m_pSubVertexList;
	vector<ID3D11Buffer*>	m_pVBList;
	vector<ATexture*>		m_pTextureList;

	vector<ATrack>			m_AnimTrack;
public:
	//FbxObject.cpp
	virtual bool SetIndexData()			override;
	virtual bool CreateVertexBuffer()	override;
	virtual bool SetVertexData()		override;
	virtual bool PostRender()			override;
	virtual bool Release()				override;
};


class AFbxLoader
{
public:
	FbxManager*		 m_pFbxManager;
	FbxImporter*	 m_pFbxImporter;
	FbxScene*		 m_pFbxScene;
	FbxNode*		 m_pRootNode;
	vector<AFbxObject*> m_pDrawList;	//Node내 Draw할 값만 저장
	vector<AFbxObject*> m_pTreeList;	//Node의 모든 정보 저장
public:
	//FbxLoader.cpp
	virtual bool	Load(string filename);
	virtual void	PreProcess(FbxNode* pNode, AFbxObject* pParent);
	virtual void	ParseMesh(AFbxObject* pObj);


	//FbxVLoader.cpp
	string			ParseMaterial(FbxSurfaceMaterial* pMtrl);
	void			ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset, 
					int iVIndex, int iUVIndex, FbxVector2& uv);
	FbxColor		ReadColor(const FbxMesh* pMesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet,
					DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4		ReadNormal(const FbxMesh* pMesh, int ictrPointIndex, int iVcounter);
	int				GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMtrlSetList);

public:
	//Animation 추가
	TMatrix			DxConvertMatrix(TMatrix m);
	TMatrix			ConvertMatrix(FbxMatrix& m);
	TMatrix			ConvertAMatrix(FbxAMatrix& m);
	void			ParseAnimation();

public:
	//FbxLoader.cpp
	virtual bool	Init() ;
	virtual bool	Render();
	virtual bool	Frame();
	virtual bool	Release();
};

