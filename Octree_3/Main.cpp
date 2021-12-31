#include "Octree.h"
#include <windows.h>

int main()
{
	ABox a(AVector3(10.0f, 10.0f, 10.0f), AVector3(50.0f, 50.0f, 50.0f));
	ABox b(AVector3(-5.0f, -5.0f, -5.0f), AVector3(15.0f, 15.0f, 15.0f));
	ABox rtUnion = ACollision::UnionRegion(a, b);
	ABox rtIntersect;

	if (ACollision::IntersectRegion(a, b, &rtIntersect))
	{
		cout << "충돌하였습니다!\n";
	}
	{
		AOctree g_Octree;
		g_Octree.Init(100, 100, 100);

		for (int iObj = 0; iObj < 5; iObj++)
		{
			AVector3 pos, rect;
			pos.x = (float)(rand() % 100);
			pos.y = (float)(rand() % 100);
			pos.z = (float)(rand() % 100);

			rect.x = (float)(rand() % 100);//+ 1.0f;
			rect.y = (float)(rand() % 100);//+ 1.0f;
			rect.z = (float)(rand() % 100);//+ 1.0f;

			g_Octree.AddObject(new AObject(pos, rect));
		}
		float fSec = 0.0f;
		while (fSec < 5)
		{
			Sleep(10);
			g_Octree.Frame(10.0f / 1000.0f);
			fSec += 10.0f / 1000.0f;
		}
		ANode::g_Counter--;
		g_Octree.Release();
	}	
	cout << "\n\n\t\t\t이제 좀 쉬자!";
}

