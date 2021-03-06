#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // rand(), srand()
#include <conio.h>
#include <time.h> // time()

typedef struct TStudentNode
{
	char	m_szName[20];
	int		m_iAge;
	int     m_iKor;
	int     m_iEng;
	int     m_iMat;
	int     m_iTotal;
	float   m_fAverage;
	char	m_strAddress[50];
	TStudentNode* pNext;
}TNode;

TNode* g_pNodeHead = 0;
TNode* g_pNodeTail = 0;
TNode* g_pFindNode = 0;
int			g_iNumCounter = 0;
//  신규 노드 생성 및 연결리스트 연결
void		NewLink(const char* pName, int m_iAge, const char* pAddr, int* pData = 0);
// 초기 연결리스트 구축
void		RandData();
// pDelNode를 연결리스트에서 삭제
TNode* DelLink(TNode* pDelNode);
// 전체 연결리스트 삭제
void		AllDeleteLink();
// 파일로 부터 로드 및 연결리스트 구축
void		LoadLink(const char* pFileName);
// 연결리스트 전체를 파일로 저장.
void		SaveData(const char* pSaveFileName);
// pFindName이름의 노드를 반환한다.
TNode* FindName(const char* pFindName);
// pFindNode를 출력한다.
void PrintData(TNode* pFindNode);
// 전체 연결리스트를 출력한다.
void PrintAllData();
// pFindNode 의 데이터 수정.
TNode* UpdateData(TNode* pFindNode);
// g_pFindNode 노드 뒤에 삽입한다.
bool InsertLink(TNode* pFindNode, const char* pName, int m_iAge, const char* pAddr, int* pData = 0);

