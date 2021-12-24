#include "Quadtree.h"

void main()
{
	AQuadtree tree;
	tree.Init(100, 100, 2);
	for (int iObj = 0; iObj < 10; iObj++)
	{
		int iX = rand() % 100;
		int iY = rand() % 100;
		//tree.AddObject(iX, iY);
	}
	tree.PrintList(tree.m_pRootNode);
}