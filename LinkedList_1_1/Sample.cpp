#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 5
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//1) ����ü OK
//2) main OK
//3) ���� ����, ��� ���� -> ����
//4) ��� ���� OK
//5) ȭ�� ���
//�ε��ؼ� ����, ȭ�� ���, ��� ������ ����

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

AUser* NewNode() //��� ����
{
	AUser* pUser = (AUser*)malloc(sizeof(AUser));
	pUser->m_Idx = imaxcount;
	pUser->m_Kor = rand() % 100;
	pUser->m_Eng = rand() % 100;
	return pUser;
}
void AddLink(AUser* pUser)
{
	if (StartUser == NULL) //start�� ������ pUser�� Start�� End�� ���� �� maxcounter ����
	{
		StartUser = pUser;
		EndUser = pUser;
		imaxcount++;
	}
	//start�� ������ end -> next �� pUser, end�� ������ �� maxcounter ����
	EndUser->pNext = pUser;
	EndUser = pUser;
	imaxcount++;
}

FILE* Create() //ó���� ���� fw�� ����Ű�� ���������ͷ� ��ȯ, data���� ����
{
	for(int iData =0; iData < MaxCount; iData++)
	{
		AddLink(NewNode()); // ���ִ� Data count��ŭ ����ó��
	}

	FILE* fpWrite = fopen("Sample.txt", "r+b"); //���̳ʸ� �б�(r+ : ���� ����� ������ ����)
	if (fpWrite == NULL)
	{
		fpWrite = fopen("Sample.txt", "wb"); //���̳ʸ��� �ۼ�
		int count = imaxcount;
		fwrite(&count, sizeof(int), 1, fpWrite); // ���Ḯ��Ʈ 1�پ� ó��
		for (AUser* user = StartUser; user != NULL; user = user->pNext)
		{
			fwrite(user, sizeof(AUser), 1, fpWrite);
		}
		fseek(fpWrite, 0, SEEK_SET);
	}
	return fpWrite;
}

void SaveNLoad() //���� ���� �� �ε�
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
void AllDelete() //��� ��� ���ʴ�� ����, �� ���� �� pNext�� ���� ��� �������ֱ�
{
	AUser* pNext = StartUser;

	while(pNext) //pNext�� �����ҵ��� ���ʴ�� ���� �� ����ó��
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
