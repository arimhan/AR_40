#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>

//�������Ḯ��Ʈ
//����� �����Լ� ��� 
//while(), if ~ else , for()

struct ANode
{
	char cName;
	struct ANode* pNext;
};
ANode* g_pHead = 0;
ANode* CircularLinkedList(char* strList);
ANode* NextNodeDelete(ANode* p);
void JosephProblem(ANode* p, int n);