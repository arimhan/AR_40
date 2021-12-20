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

// ���� ����
ANode* g_pArray[7];
queue<ANode*> g_Queue;
int g_iValue = 0;

void CreateBinaryNode(ANode* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->pLeft = new ANode(++g_iValue); //��������
	pNode->pRight = new ANode(++g_iValue);

	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1; //�ڽĳ�� ������ ���� depth����ó��

	CreateBinaryNode(pNode->pLeft);
	CreateBinaryNode(pNode->pRight); //���ȣ�⿡ ���� 2��Ʈ�� ����
}

void PreOrderPrint(ANode* pNode) 
//������ȸ : ��Ʈ->����
// 0 1 3 4 2 5 6
{
	if (pNode == nullptr) return;
	cout << pNode->iValue;
	PreOrderPrint(pNode->pLeft);
	PreOrderPrint(pNode->pRight);
}
void InOrderPrint(ANode* pNode) 
//������ȸ : ���� ����->�ڽ�->����
// 3 1 4 0 5 2 6
{
	if (pNode == nullptr) return;
	InOrderPrint(pNode->pLeft);
	cout << pNode->iValue;
	InOrderPrint(pNode->pRight);
}
void PostOrderPrint(ANode* pNode) 
//������ȸ : ���� ����-> ����...�� ������ �θ���
// 3 4 1 5 6 2 0
{
	if (pNode == nullptr) return;
	PostOrderPrint(pNode->pLeft);
	PostOrderPrint(pNode->pRight);
	cout << pNode->iValue;
}
void LevelOrderPrint(ANode* pNode) // �� �κ��� �� ���� �Ȱ�.
{	// Level������� ��ȸ -> root���� �� ���� ����������
	// 0 1 2 3 4 5 6
	do 
	{
		if (pNode->pLeft != nullptr)
			g_Queue.push(pNode->pLeft);
		if (pNode->pRight != nullptr)
			g_Queue.push(pNode->pRight);
		//pNode�� ����, �������� ���� ������ �ش� ���� �־��ְ�

		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		cout << pNode->iValue;
		//pNode�� front�� �������༭ iValue���� ����Ѵ�.

		g_Queue.pop();
		//�� ��� �� pop(����)

		//if (g_Queue.empty()) break;
		//pNode = g_Queue.front();
		//cout << pNode->iValue; //�� ����� 2���̸� 0, 1,1,2,2..�̷������� ��µǰ�..
		// �� ������ �� ���� ���� 0,1,2,1,2...�� �Ǿ����.


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