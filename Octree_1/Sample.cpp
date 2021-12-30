#include "Octree.h"
//지금 얘가 QuadTree기반이라 수정 다 해야댐...
// Quad -> Oct 변환 (Z값, collision계산 수정) 
// 정적 -> 동적 -> 프레임 

void main()
{
	AOctree tree;
	tree.Init(100, 100, 5);
	for (int iObj = 0; iObj < 10; iObj++)
	{
		AObject* pObj = new AObject();
		pObj->SetPos((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100));

		float hw = (float)(rand() % 10) + 10;
		float hh = (float)(rand() % 10) + 10;
		float hz = (float)(rand() % 10) + 10;

		//-------------- 정적 obj --------------
		AVector3 vMin;
		vMin.x = pObj->m_vPos.x - hw;
		vMin.y = pObj->m_vPos.y - hh;
		vMin.z = pObj->m_vPos.z - hz;
		ABox rt(vMin, hw * 2.0f, hh * 2.0f, hz * 2.0f);
		pObj->SetBox(rt);
		tree.AddObject(pObj);

		//-------------- 동적 obj --------------
		AVector3 vMin;
		vMin.x = pObj->m_vPos.x - hw;
		vMin.y = pObj->m_vPos.y - hh;
		ABox rt(vMin, hw * 2.0f, hh * 2.0f, hz * 2.0f);
		pObj->SetBox(rt);
		tree.AddObject(pObj); //AddDynamicObject 
	}


	//AObject* ObjList[10]; 동적 배열 10개만 처리 
	//출력
	// for문으로 동적 obj를 전부 지워줌 PrintObjList
	tree.PrintList(tree.m_pRootNode);
}