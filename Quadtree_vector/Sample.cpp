#include "Quadtree.h"

void main()
{
	



	//AVector2 *a = new AVector2(3,2);
	//cout << "vector x : " << a->x << ",  y " << a->y << endl;
	float fvalue = 3.0f;
	AVector2 *one = new AVector2(3, 2);
	cout << "vector x : " << one->x << ",  y " << one->y << endl;
	AVector2 *two = new AVector2(4, 5);
	AVector2 dir = *one - *two;

	dir = dir.Normalization();
	AVector2 newPos = *two + dir * fvalue;



	/*AQuadtree tree;
	tree.Init(100, 100, 2);
	for (int iObj = 0; iObj < 10; iObj+/8+)
	{
		int iX = rand() % 100;
		int iY = rand() % 100;
		tree.AddObject(iX, iY);
	}
	tree.PrintList(tree.m_pRootNode);*/
	return;
}