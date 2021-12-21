#include "Quadtree.h"
// ÄõµåÆ®¸® https://x123.tistory.com/35 // https://ottuging.tistory.com/16?category=824346


void main()
{
	AQuadtree tree;
	tree.Init(100, 100, 2); // width, hieght, depth
	for (int iObj = 0; iObj < 10; iObj++)
	{
		int iX = rand() % 100;
		int iY = rand() % 100;
		tree.AddObject(iX, iY);
	}
	tree.PrintList(tree.m_pRootNode);
}