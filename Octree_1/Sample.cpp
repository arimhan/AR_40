#include "Octree.h"

void main()
{
	AOctree tree;
	tree.Init(100, 100, 2);
	for (int iObj = 0; iObj < 10; iObj++)
	{
		AObject* pObj = new AObject();
		pObj->SetPos((float)(rand() % 100), (float)(rand() % 100));

		float hw = (float)(rand() % 10) + 10;
		float hh = (float)(rand() % 10) + 10;
		AVector2 vMin;
		vMin.x = pObj->m_vPos.x - hw;
		vMin.y = pObj->m_vPos.y - hh;
		ARect rt(vMin, hw * 2.0f, hh * 2.0f);
		pObj->SetRect(rt);
		tree.AddObject(pObj);
	}
	tree.PrintList(tree.m_pRootNode);
}