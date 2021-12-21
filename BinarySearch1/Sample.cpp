#include <iostream>
#include <queue>
using namespace std;
//이중포인터, 배열버전

struct ANode 
{
	int iDepth;
	int iValue;
	ANode* m_pChildNode[2]; 
	ANode() 
	{
		iValue = -1;
		m_pChildNode[0] = nullptr;
		m_pChildNode[1] = nullptr;
	}
	ANode(int i)
	{
		iValue = i;
		m_pChildNode[0] = nullptr;
		m_pChildNode[1] = nullptr;
	}
	~ANode()
	{
		delete m_pChildNode[0];
		delete m_pChildNode[1];
	}
};

// 전역 셋팅
ANode** g_ppArray = nullptr;
queue<ANode*> g_Queue;
int g_iValue = 0;

void CreateBinaryNode(ANode* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->m_pChildNode[0] = new ANode(++g_iValue); //전위증가
	g_ppArray[g_iValue] = pNode->m_pChildNode[0];
	pNode->m_pChildNode[1] = new ANode(++g_iValue);
	g_ppArray[g_iValue] = pNode->m_pChildNode[1];

	pNode->m_pChildNode[0]->iDepth = pNode->iDepth + 1;
	pNode->m_pChildNode[1]->iDepth = pNode->iDepth + 1; //자식노드 생성에 따른 depth증가처리

	CreateBinaryNode(pNode->m_pChildNode[0]);
	CreateBinaryNode(pNode->m_pChildNode[1]); //재귀호출에 따른 2진트리 생성
}

void PreOrderPrint(ANode* pNode) 
//전위순회 : 루트->왼쪽
// 0 1 3 4 2 5 6
{
	if (pNode == nullptr) return;
	cout << pNode->iValue;
	PreOrderPrint(pNode->m_pChildNode[0]);
	PreOrderPrint(pNode->m_pChildNode[1]);
}
void InOrderPrint(ANode* pNode) 
//중위순회 : 왼쪽 리프->자식->리프
// 3 1 4 0 5 2 6
{
	if (pNode == nullptr) return;
	InOrderPrint(pNode->m_pChildNode[0]);
	cout << pNode->iValue;
	InOrderPrint(pNode->m_pChildNode[1]);
}
void PostOrderPrint(ANode* pNode) 
//후위순회 : 왼쪽 리프-> 리프...맨 마지막 부모노드
// 3 4 1 5 6 2 0
{
	if (pNode == nullptr) return;
	PostOrderPrint(pNode->m_pChildNode[0]);
	PostOrderPrint(pNode->m_pChildNode[1]);
	cout << pNode->iValue;
}
void LevelOrderPrint(ANode* pNode) // 이 부분이 잘 이해 안감.
{	// Level순서대로 순회 -> root부터 맨 우측 리프노드까지
	// 0 1 2 3 4 5 6
	do 
	{
		if (pNode->m_pChildNode[0] != nullptr)
			g_Queue.push(pNode->m_pChildNode[0]);
		if (pNode->m_pChildNode[1] != nullptr)
			g_Queue.push(pNode->m_pChildNode[1]);
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
	int iMaxDepth = 2;
	int cnt = pow(2, iMaxDepth + 1) - 1;
	//pRoot제외한 자식~리프노드 수

	g_ppArray = new ANode * [cnt];

	ANode* pRoot = new ANode(0);
	if (pRoot == nullptr) return;
	pRoot->iDepth = 0;
	g_ppArray[0] = pRoot;
	CreateBinaryNode(pRoot);
	PreOrderPrint(pRoot);
	cout << endl;
	InOrderPrint(pRoot);
	cout << endl;
	PostOrderPrint(pRoot);
	cout << endl;
	LevelOrderPrint(pRoot);

	delete pRoot;
}