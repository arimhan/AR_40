#include "Problem.h"
ANode* CircularLinkedList(char* strList)
{
	ANode* pNode = 0;
	pNode = new ANode; //(ANode*)malloc(sizeof(ANode));
	pNode->cName = strList[0];
	g_pHead = pNode;

	int iMaxCount = strlen(strList);
	for (int iCount = 1; iCount < iMaxCount; iCount++)
	{
		pNode->pNext = new ANode;
		pNode = pNode->pNext;
		pNode->cName = strList[iCount];
	}
	pNode->pNext = g_pHead;
	return g_pHead;
}

// 노드 삭제. 단일 연결 리스트에서는 이전 노드를 알 수 없기 때문에 pNode는 삭제하려는 노드의 이전 노드.
ANode* NextNodeDelete(ANode* pNode)
{
	ANode* pDelNode = pNode->pNext;
	pNode->pNext = pDelNode->pNext;
	free(pDelNode);
	return pNode->pNext;
}

void JosephProblem(ANode* p, int n) {

}