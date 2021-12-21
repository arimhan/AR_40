#include <iostream>
#include <queue>
using namespace std;
//����������, �迭����

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

// ���� ����
ANode** g_ppArray = nullptr;
queue<ANode*> g_Queue;
int g_iValue = 0;

void CreateBinaryNode(ANode* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->m_pChildNode[0] = new ANode(++g_iValue); //��������
	g_ppArray[g_iValue] = pNode->m_pChildNode[0];
	pNode->m_pChildNode[1] = new ANode(++g_iValue);
	g_ppArray[g_iValue] = pNode->m_pChildNode[1];

	pNode->m_pChildNode[0]->iDepth = pNode->iDepth + 1;
	pNode->m_pChildNode[1]->iDepth = pNode->iDepth + 1; //�ڽĳ�� ������ ���� depth����ó��

	CreateBinaryNode(pNode->m_pChildNode[0]);
	CreateBinaryNode(pNode->m_pChildNode[1]); //���ȣ�⿡ ���� 2��Ʈ�� ����
}

void PreOrderPrint(ANode* pNode) 
//������ȸ : ��Ʈ->����
// 0 1 3 4 2 5 6
{
	if (pNode == nullptr) return;
	cout << pNode->iValue;
	PreOrderPrint(pNode->m_pChildNode[0]);
	PreOrderPrint(pNode->m_pChildNode[1]);
}
void InOrderPrint(ANode* pNode) 
//������ȸ : ���� ����->�ڽ�->����
// 3 1 4 0 5 2 6
{
	if (pNode == nullptr) return;
	InOrderPrint(pNode->m_pChildNode[0]);
	cout << pNode->iValue;
	InOrderPrint(pNode->m_pChildNode[1]);
}
void PostOrderPrint(ANode* pNode) 
//������ȸ : ���� ����-> ����...�� ������ �θ���
// 3 4 1 5 6 2 0
{
	if (pNode == nullptr) return;
	PostOrderPrint(pNode->m_pChildNode[0]);
	PostOrderPrint(pNode->m_pChildNode[1]);
	cout << pNode->iValue;
}
void LevelOrderPrint(ANode* pNode) // �� �κ��� �� ���� �Ȱ�.
{	// Level������� ��ȸ -> root���� �� ���� ����������
	// 0 1 2 3 4 5 6
	do 
	{
		if (pNode->m_pChildNode[0] != nullptr)
			g_Queue.push(pNode->m_pChildNode[0]);
		if (pNode->m_pChildNode[1] != nullptr)
			g_Queue.push(pNode->m_pChildNode[1]);
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
	int iMaxDepth = 2;
	int cnt = pow(2, iMaxDepth + 1) - 1;
	//pRoot������ �ڽ�~������� ��

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