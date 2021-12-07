#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 20
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
//* ~b는 바이너리로 출력

struct AUser
{
	int m_iIndex;
	int m_iKor;
	AUser* pNext;
	//AUser* pPrev;
};

struct AReturn
{
	FILE* fp;
	AUser* List;
};
int g_iMaxUserCounter = 0;
AUser* g_pHeadUserList = 0;
AUser* g_pEndUser = 0;


//1) 데이터 초기화 및 입력
AUser* NewNode();
FILE* Create();

//2) 파일생성 후 저장
int Insert(FILE* fp);

//3) 로드해서 저장
void Load();

//4) 화면 출력
void Draw(int iCounter);

//5) 모든 데이터 삭제(동적 할당 제거)
void AllDelete();

void main()//int argc, char* argv[]) cmd나 디버그에서 값을 인자로 받고 싶으면 다음과 같이 처리
{
	FILE* fp = Create();
	fclose(fp);
	AllDelete();
	Load();
	Draw(g_iMaxUserCounter);
	AllDelete();
}

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
		for (int iAdd = 0; iAdd < iCounterRead; iAdd ++)
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
