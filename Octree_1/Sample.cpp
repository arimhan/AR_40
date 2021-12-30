#include "Octree.h"
//���� �갡 QuadTree����̶� ���� �� �ؾߴ�...
// Quad -> Oct ��ȯ (Z��, collision��� ����) 
// ���� -> ���� -> ������ 

void main()
{
	AOctree tree;
	tree.Init(100, 100, 100, 2);
	for (int iObj = 0; iObj < 15; iObj++)
	{
		AObject* pObj = new AObject();
		pObj->SetPos((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100));

		float hw = (float)(rand() % 100) + 4;
		float hh = (float)(rand() % 100) + 4;
		float hz = (float)(rand() % 100) + 4;

		//-------------- ���� obj --------------
		AVector3 vMin;
		vMin.x = pObj->m_vPos.x - hw;
		vMin.y = pObj->m_vPos.y - hh;
		vMin.z = pObj->m_vPos.z - hz;
		ABox rt(vMin, hw * 2.0f, hh * 2.0f, hz * 2.0f);
		pObj->SetBox(rt);
		tree.AddObject(pObj);

		////-------------- ���� obj --------------
		//AVector3 vMin;
		//vMin.x = pObj->m_vPos.x - hw;
		//vMin.y = pObj->m_vPos.y - hh;
		//ABox rt(vMin, hw * 2.0f, hh * 2.0f, hz * 2.0f);
		//pObj->SetBox(rt);
		//tree.AddObject(pObj); //AddDynamicObject 
	}
	tree.PrintObjList(tree.m_pRootNode);

	//AObject* ObjList[10]; ���� �迭 10���� ó�� 
	//���
	// for������ ���� obj�� ���� ������ PrintObjList
	//for (int i = 0; i < 10; i++)
	//{
	//	delete Objectlist
	//}
}