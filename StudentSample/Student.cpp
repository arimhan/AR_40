#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 20
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "Student.h"


AUser* NewNode()
{
	AUser* pUser = (AUser*)malloc(sizeof(AUser));
	pUser->m_iIndex = g_iMaxUserCounter;
	pUser->m_iKor = rand() % 100;
	pUser->pNext = NULL;
	return pUser;
}
void AddLink(AUser* pUser)
{
	if (g_pHeadUserList == NULL)
	{
		g_pHeadUserList = pUser;
		g_pEndUser = pUser;
		g_iMaxUserCounter++;
		return;
	}
	g_pEndUser->pNext = pUser;
	g_pEndUser = pUser;
	g_iMaxUserCounter++;
}
FILE* Create()
{
	for (int iData = 0; iData < MaxCount; iData++)
	{
		AddLink(NewNode());
	}
	FILE* fpWrite = fopen("Sample.txt", "r+b");
	if (fpWrite == NULL)
	{
		fpWrite = fopen("Sample.txt", "wb");
		int iCounter = g_iMaxUserCounter;
		fwrite(&iCounter, sizeof(int), 1, fpWrite);
		for (AUser* user = g_pHeadUserList; user != NULL; user = user->pNext)
		{
			fwrite(user, sizeof(AUser), 1, fpWrite);
		}
		fseek(fpWrite, 0, SEEK_SET);
	}
	return fpWrite;
}
void AllDelete()
{
	AUser* pNext = g_pHeadUserList;
	while (pNext)
	{
		AUser* pDeleteUser = pNext;
		pNext = pDeleteUser->pNext;
		free(pDeleteUser);
		pDeleteUser = NULL;
	}
	g_pHeadUserList = NULL;
}
int Insert(FILE* fp)
{
	return g_iMaxUserCounter;
}
void Load()
{
	FILE* fpRead = fopen("Sample.txt", "rb");
	int iCounterRead = 0;
	fread(&iCounterRead, sizeof(int), 1, fpRead);

	if (fpRead != NULL)
	{
		for (int iAdd = 0; iAdd < iCounterRead; iAdd++)
		{
			AUser* pUser = (AUser*)malloc(sizeof(AUser));
			memset(pUser, 0, sizeof(AUser));
			fread(pUser, sizeof(AUser), 1, fpRead);
			pUser->pNext = 0;
			AddLink(pUser);
		}

		fclose(fpRead);
		fpRead = NULL;
	}
}
void Draw(int iCounter)
{
	for (AUser* user = g_pHeadUserList; user != NULL; user = user->pNext)
	{
		printf("%d %d\n", user->m_iIndex, user->m_iKor);
	}
}