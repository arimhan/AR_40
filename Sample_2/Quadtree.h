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
	int			 m_iMaxDepth;
	ANode*		 m_pRootNode;
	static int	 g_iCount;

public:
	list<AMapObj*>	m_pObjList;
	vector<ANode*>	g_pDrawLeafNodes;
	vector<ANode*>	g_pLeafNodes;
	queue<ANode*>	g_pQueue;
	int				g_iValue = 0;

public:
	void		Build(int iWidth, int iHeight, int iMaxDepth);
	void		Build(AMap* pMap, int iMaxDepth);
	ANode*		CreateNode(ANode* pParent, float x, float y, float w, float h);

	void		BuildTree(ANode* pParent);
	ABox		GenBoundingBox(ANode* pNode);
	TVector2	GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	bool		AddObject(AMapObj* pObj);
	bool		AddDynamicObject(AMapObj* pObj);
	void		DelDynamicObject(ANode* pNode);

public:
	ANode*		FindNode(ANode* pNode, ABox& box);
	bool		CheckBox(ABox& abox, ABox& bbox);

public:
	void		SetIndexData(ANode* pNode);
	bool		CreateIndexBuffer(ANode* pNode);
	void		Update(ACamera* pCamera);
	void		Render();
	void		RenderObject(ANode* pNode);
	void		RenderTile(ANode* pNode);

public:
	void		PrintObjList(ANode* pNode);

public:
	AQuadtree();
	virtual ~AQuadtree();
};


