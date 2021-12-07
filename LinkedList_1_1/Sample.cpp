#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 5
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//1) 구조체 OK
//2) main OK
//3) 파일 생성, 노드 생성 -> 저장
//4) 노드 삭제 OK
//5) 화면 출력
//로드해서 저장, 화면 출력, 모든 데이터 삭제

struct AUser
{
	int m_Idx;
	int m_Kor;
	int m_Eng;
	AUser* pNext;
};


int imaxcount = 0;
AUser* StartUser = 0;
AUser* EndUser = 0;

AUser* NewNode() //노드 생성
{
	AUser* pUser = (AUser*)malloc(sizeof(AUser));
	pUser->m_Idx = imaxcount;
	pUser->m_Kor = rand() % 100;
	pUser->m_Eng = rand() % 100;
	return pUser;
}
void AddLink(AUser* pUser)
{
	if (StartUser == NULL) //start가 없으면 pUser를 Start와 End에 연결 후 maxcounter 증가
	{
		StartUser = pUser;
		EndUser = pUser;
		imaxcount++;
	}
	//start가 있으면 end -> next 에 pUser, end에 연결한 뒤 maxcounter 증가
	EndUser->pNext = pUser;
	EndUser = pUser;
	imaxcount++;
}

FILE* Create() //처리할 파일 fw를 가리키는 파일포인터로 반환, data파일 생성
{
	for(int iData =0; iData < MaxCount; iData++)
	{
		AddLink(NewNode()); // 들어가있는 Data count만큼 연결처리
	}

	FILE* fpWrite = fopen("Sample.txt", "r+b"); //바이너리 읽기(r+ : 내용 덮어쓰고 없으면 생성)
	if (fpWrite == NULL)
	{
		fpWrite = fopen("Sample.txt", "wb"); //바이너리로 작성
		int count = imaxcount;
		fwrite(&count, sizeof(int), 1, fpWrite); // 연결리스트 1줄씩 처리
		for (AUser* user = StartUser; user != NULL; user = user->pNext)
		{
			fwrite(user, sizeof(AUser), 1, fpWrite);
		}
		fseek(fpWrite, 0, SEEK_SET);
	}
	return fpWrite;
}

void SaveNLoad() //파일 생성 및 로드
{ 
	FILE* fpRead = fopen("Sample.txt", "rb");
	int countRead = 0;

	if (fpRead == NULL)
	{
		for (int iAdd = 0; iAdd < countRead; iAdd++)
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
void Draw() { return; }
void AllDelete() //모든 노드 차례대로 삭제, 단 삭제 전 pNext에 이전 노드 연결해주기
{
	AUser* pNext = StartUser;

	while(pNext) //pNext가 존재할동안 차례대로 연결 및 삭제처리
	{
		AUser* DeleteUser = pNext;
		pNext = DeleteUser->pNext;
		free(DeleteUser);
		DeleteUser = NULL;
	}
	StartUser = NULL;
}

void main()
{	
	FILE* fp = Create();
	fclose(fp);
	AllDelete();
	SaveNLoad();
	//Draw();
	AllDelete();
}
