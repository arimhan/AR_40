#pragma once
#include "Node.h"
#include "Map.h"
#include "Camera.h"

class AQuadtree
{
public:
	AMap*		 m_pMap = nullptr;
	ACamera*	 m_pCamera = nullptr;
	int			 m_iWidth;
	int			 m_iHeight;
	int			 m_iLeafDepth = 0;
	int			 m_iMaxDepth = 0;
	int			 m_iNumLOD = 1;
	int			 m_iLeafLOD = 1;
	ANode*		 m_pRootNode;
	static int	 g_iCount;

public:
	list<AMapObj*>	m_pObjList;
	vector<ANode*>	g_pDrawLeafNodes;
	vector<ANode*>	g_pLeafNodes;
	queue<ANode*>	g_pQueue;
	vector<DWORD>	m_IndexList;
	ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
	int				m_iNumFace;
	int				g_iValue = 0;

public:
	void		Build(int iWidth, int iHeight, int iMaxDepth);
	void		Build(AMap* pMap, int iMaxDepth);
	ANode*		CreateNode(ANode* pParent, float x, float y, float w, float h);

	void		BuildTree(ANode* pParent);
	ABox		GenBoundingBox(ANode* pNode);
	AVector2	GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	bool		AddObject(AMapObj* pObj);
	bool		AddDynamicObject(AMapObj* pObj);
	void		DelDynamicObject(ANode* pNode);

public:
	ANode*		FindNode(ANode* pNode, ABox& box);
	bool		CheckBox(ABox& abox, ABox& bbox);

public:
	void		SetIndexData(ANode* pNode, int iLodLevel);
	bool		CreateIndexBuffer(ANode* pNode, int iLodLevel);
	void		Update(ACamera* pCamera);

	bool		PreRender();
	bool		Render();
	bool		PostRender();

	void		RenderObject(ANode* pNode);
	void		RenderTile(ANode* pNode);

public:
	//void		PrintObjList(ANode* pNode);
public:
	void		FindNeighborNode();
	ANode*		CheckBoxtoPoint(A::AVector3 p);
	void		GetRatio(ANode* pNode);
	int			GetLodType(ANode* pNode);
	int			UpdateIndexList(ANode* pNode, DWORD dwCurentIndex, DWORD dwNumLevel);
	int			SetLodIndexBuffer(ANode* pNode, DWORD& dwCurentIndex, 
				DWORD dwA, DWORD dwB, DWORD dwC, DWORD dwType);
#ifdef _DEBUG
public:
	ABoxObj		m_BoxDebug;
	void		DrawDebugInit(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	void		DrawDebugRender(ABox* pBox);
#endif
public:
	AQuadtree();
	virtual ~AQuadtree();
};


