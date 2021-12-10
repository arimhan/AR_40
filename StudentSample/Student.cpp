#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 20
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "Student.h"


AUser* AStudent::NewNode()
{
	AUser* pUser = (AUser*)malloc(sizeof(AUser));
	pUser->m_iIndex = g_Maxcount;
	pUser->m_iKor = rand() % 100;
	pUser->pNext = NULL;
	return pUser;
}
void AStudent::AddLink(AUser* pUser)
{
	if (g_Start == NULL)
	{
		g_Start = pUser;
		g_End = pUser;
		g_Maxcount++;
		return;
	}
	g_End->pNext = pUser;
	g_End->pNext = pUser;
	g_Maxcount++;
}
FILE* AStudent::Create()
{
	for (int iData = 0; iData < MaxCount; iData++)
	{
		AddLink(NewNode());
	}
	FILE* fpWrite = fopen("Sample.txt", "r+b");
	if (fpWrite == NULL)
	{
		fpWrite = fopen("Sample.txt", "wb");
		int iCounter = g_Start;
		fwrite(&iCounter, sizeof(int), 1, fpWrite);
		for (AUser* user = g_Start; user != NULL; user = user->pNext)
		{
			fwrite(user, sizeof(AUser), 1, fpWrite);
		}
		fseek(fpWrite, 0, SEEK_SET);
	}
	return fpWrite;
}
void AStudent::AllDelete()
{
	AUser* pNext = g_Start;
	while (pNext)
	{
		AUser* pDeleteUser = pNext;
		pNext = pDeleteUser->pNext;
		free(pDeleteUser);
		pDeleteUser = NULL;
	}
	g_Start = NULL;
}
int AStudent::Insert(FILE* fp)
{
	return g_Start;
}
void AStudent::Load()
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
void AStudent::Draw(int iCounter)
{
	for (AUser* user = g_Start; user != NULL; user = user->pNext)
	{
		printf("%d %d\n", user->m_iIndex, user->m_iKor);
	}
}