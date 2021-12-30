#include "Octree.h"
#include <windows.h>

int main()
{
	{
		Box a(Vector3(-10.0f, -10.0f, -10.0f), Vector3(10.0f, 10.0f, 10.0f));
		Box b(Vector3(-5.0f, -5.0f, -5.0f), Vector3(15.0f, 15.0f, 15.0f));
		Box rtUnion = Collision::UnionRegion(a, b);
		Box rtIntersect;


		Octree g_iCounter;
		g_iCounter.Init(100, 100, 100);

		for (int iObj = 0; iObj < 3; iObj++)
		{
			Vector3 pos, rect;
			pos.x = (float)(rand() % 100);
			pos.y = (float)(rand() % 100);
			pos.z = (float)(rand() % 100);

			rect.x = (float)(rand() % 10) + 1.0f;
			rect.y = (float)(rand() % 10) + 1.0f;
			rect.z = (float)(rand() % 10) + 1.0f;

			g_iCounter.AddObject(new Object(pos, rect));
		}
		Node::g_Counter--;
		g_iCounter.Release();
	}
	cout << "Ãæµ¹.";

}

