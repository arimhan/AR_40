#pragma once
#include "Object3D.h"
#include <fbxsdk.h>
#include "Camera.h"


struct PNCT
{
	T::TVector3 p;
	T::TVector3 n;
	T::TVector4 c;
	T::TVector2 t;
};
struct AVertexIW
{
	float			i[4]; //index
	float			w[4]; //weight
	T::TVector3		tan;  //tangent
	AVertexIW()
	{
		i[0] = i[1] = i[2] = i[3] = 0;
		w[0] = w[1] = w[2] = w[3] = 0.0f;
	}
};
//멀티스트림 (VB[0], VB[1])
//InputLayout (PNCT IW) -> 정점쉐이더에 전달

struct ATrack
{
	UINT	iFrame;
	TMatrix matTrack;

	//SRT 값
	T::TVector3		s;
	T::TQuaternion	r; //Rotation은 TQuaternion로 해야 짐벌현상이 발생하지 않는다.
	T::TVector3		t;
};

struct AWeight					//가중치
{
	vector<int>		Index;			//영향을 미치는 행렬의 인덱스
	vector<float>	Weight;			//가중치
	void InsertWeight(int iBoneIndex, float fBoneWeight);

	AWeight()
	{
		Index.resize(8);
		Weight.resize(8);
	}
};

class AFbxModel : public AObject3D
{
public:
	//Animation 추가
	int			m_iIndex = -1;
	bool		m_bSkinned = false;

	TMatrix		m_matLocal;
	TMatrix		m_matAnim;

	FbxNode*	m_pFbxParent = nullptr;
	FbxNode*	m_pFbxNode = nullptr;
	AFbxModel	* m_pParentObj = nullptr;

	wstring		m_szTexFileName;

	//SubMaterial
	vector<wstring>			m_szTexFileList;

	using ASubVertex = vector<AVertex>;
	using ASubVertexIW = vector<AVertexIW>;
	vector<ASubVertex>		m_pSubVertexList;
	vector<ASubVertexIW>	m_pSubIWVertexList;
	vector<AWeight>			m_WeightList;

	vector<ID3D11Buffer*>	m_pVBList;
	vector<ID3D11Buffer*>	m_pVBWeightList;
	vector<ATexture*>		m_pTextureList;

	vector<ATrack>			m_AnimTrack;
	map<wstring, TMatrix>	m_dxMatrixBindPoseMap;
	ACamera*				m_pMainCamera;

public:

	virtual bool SetVertexData()		override;
	virtual bool CreateVertexBuffer()	override;

	virtual bool SetIndexData()			override;
	virtual bool CreateIndexBuffer()	override;

	virtual bool PostRender()			override;
	virtual bool Release()				override;

	virtual void GenAABB()				override;
};

struct AScene
{
	UINT  iStart;
	UINT  iEnd;
	UINT  iFrameSpeed;
};

class AFbxImporter : public AObject3D
{
public:
	AScene			m_Scene;
	float			m_fDir = 1.0f;
	float			m_fTimer = 0.0f;
	float			m_fSpeed = 1.0f;
	
	ABoneWorld		m_matBoneArray;
public:
	FbxManager*		m_pFbxManager;
	FbxImporter*	m_pFbxImporter;
	FbxScene*		m_pFbxScene;
	FbxNode*		m_pRootNode;

	map<FbxNode*, int>			m_pFbxNodeMap;
	map<wstring, AFbxModel*>	m_pFbxModelMap;

	vector<AFbxModel*> m_pDrawList;	//Node내 Draw할 값만 저장
	vector<AFbxModel*> m_pTreeList;	//Node의 모든 정보 저장
	ID3D11Buffer*	   m_pBoneCB = nullptr;
public:

	bool			Load(ID3D11Device* pd3dDevice, wstring filename);
	virtual bool	Load(string filename);
	virtual void	PreProcess(FbxNode* pNode, AFbxModel* pParent);
	virtual void	ParseMesh(AFbxModel* pObj);
	string			ParseMaterial(FbxSurfaceMaterial* pMtrl);

	//FbxVLoader
	void			ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset,
					int iVIndex, int iUVIndex, FbxVector2& uv);
	FbxColor		ReadColor(const FbxMesh* pMesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet,
					DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4		ReadNormal(const FbxMesh* pMesh, int ictrPointIndex, int iVcounter);
	FbxVector4		ReadNormal(const FbxMesh* pMesh, DWORD dwVertexNormalCount,FbxLayerElementNormal* pVertexNormalSets,
					int ictrPointIndex, int iVIndex);
	FbxVector4		ReadTangent(const FbxMesh* pMesh, DWORD dwVertexTangentCount, FbxGeometryElementTangent* pVertexTangentSets,
					DWORD dwDCCIndex, DWORD dwVertexIndex);
	bool			ParseMeshSkinning(FbxMesh* pFbxMesh, AFbxModel* pObject);
	int				GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMtrlSetList);

public:
	TMatrix			DxConvertMatrix(TMatrix m);
	TMatrix			ConvertMatrix(FbxMatrix& m);
	TMatrix			ConvertAMatrix(FbxAMatrix& m);
	void			ParseAnimation();

public:
	virtual bool	Init();
	virtual bool	Render();
	virtual bool	Frame();
	virtual bool	Release();
	virtual bool	CreateConstantBuffer(ID3D11Device* pDevice);
};



