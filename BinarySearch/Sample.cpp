#include <iostream>
#include <queue>
using namespace std;

struct ANode 
{
	int iDepth;
	int iValue;
	//ANode* m_pChildNode[2]; 
	ANode* pLeft; //m_pChildNode[0];
	ANode* pRight; //m_pChildNode[0];

	ANode() 
	{
		iValue = -1;
		pLeft = nullptr;
		pRight = nullptr;
	}
	ANode(int i)
	{
		iValue = i;
		pLeft = nullptr;
		pRight = nullptr;
	}
	~ANode()
	{
		delete pLeft;
		delete pRight;
	}
};

// 전역 셋팅
ANode* g_pArray[7];
queue<ANode*> g_Queue;
int g_iValue = 0;

void CreateBinaryNode(ANode* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->pLeft = new ANode(++g_iValue); //전위증가
	pNode->pRight = new ANode(++g_iValue);

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1; //자식노드 생성에 따른 depth증가처리

	CreateBinaryNode(pNode->pLeft);
	CreateBinaryNode(pNode->pRight); //재귀호출에 따른 2진트리 생성
}

void PreOrderPrint(ANode* pNode) 
//전위순회 : 루트->왼쪽
// 0 1 3 4 2 5 6
{
	if (pNode == nullptr) return;
	cout << pNode->iValue;
	PreOrderPrint(pNode->pLeft);
	PreOrderPrint(pNode->pRight);
}
void InOrderPrint(ANode* pNode) 
//중위순회 : 왼쪽 리프->자식->리프
// 3 1 4 0 5 2 6
{
	if (pNode == nullptr) return;
	InOrderPrint(pNode->pLeft);
	cout << pNode->iValue;
	InOrderPrint(pNode->pRight);
}
void PostOrderPrint(ANode* pNode) 
//후위순회 : 왼쪽 리프-> 리프...맨 마지막 부모노드
// 3 4 1 5 6 2 0
{
	if (pNode == nullptr) return;
	PostOrderPrint(pNode->pLeft);
	PostOrderPrint(pNode->pRight);
	cout << pNode->iValue;
}
void LevelOrderPrint(ANode* pNode) // 이 부분이 잘 이해 안감.
{	// Level순서대로 순회 -> root부터 맨 우측 리프노드까지
	// 0 1 2 3 4 5 6
	do 
	{
		if (pNode->pLeft != nullptr)
			g_Queue.push(pNode->pLeft);
		if (pNode->pRight != nullptr)
			g_Queue.push(pNode->pRight);
		//pNode의 왼쪽, 오른쪽이 값이 있으면 해당 값을 넣어주고

		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		cout << pNode->iValue;
		//pNode에 front로 변경해줘서 iValue값을 출력한다.

		g_Queue.pop();
		//값 출력 후 pop(제거)

		//if (g_Queue.empty()) break;
		//pNode = g_Queue.front();
		//cout << pNode->iValue; //값 출력이 2번이면 0, 1,1,2,2..이런식으로 출력되고..
		// 위 문장을 한 번만 쓰면 0,1,2,1,2...가 되어버림.


	} while (pNode);
}
void main()
{
	ANode* pRoot = new ANode(0);
	g_pArray[0] = pRoot;
	pRoot->iDepth = 0;
	CreateBinaryNode(pRoot);
	PreOrderPrint(pRoot);
	cout << endl;

	InOrderPrint(pRoot);
	cout << endl;

	PostOrderPrint(pRoot);
	cout << endl;

	g_Queue.push(pRoot);
	LevelOrderPrint(pRoot);

	delete pRoot;
}