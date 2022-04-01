#pragma once
#include "Object3D.h"
#include <fbxsdk.h>

class AFbxObj : public AObject3D
{
public:
	FbxNode*	m_pFbxParent	= nullptr;
	FbxNode*	m_pFbxNode		= nullptr;
	FbxNode*	m_pParentObj	= nullptr;
	wstring m_szTexFileNmae;
public:
	bool		SetIndexData();
};

class AFbxLoader
{
public:
	FbxManager*		m_pFbxManager;
	FbxImporter*	m_pFbxImporter;
	FbxScene*		m_pFbxScene;
	FbxNode*		m_pRootNode;
	vector<AFbxObj*> m_ObjList;
public:
	virtual bool Load(string filename);
	virtual void PreProcess(FbxNode* pNode, FbxNode* pParent);
	virtual void ParseMesh(AFbxObj* pObj);
	void	ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset, 
			int iVIndex, int iUVIndex, FbxVector2& uv);
	string	ParseMaterial(FbxSurfaceMaterial* pMtrl);
public:

	virtual bool	Init() ;
	virtual bool	Render();
	virtual bool	Frame();
	virtual bool	Release();
};

