#define _CRT_SECURE_NO_WARNINGS
#define Byte 16
#include <stdio.h>
#include<stdio.h>
#include<string.h>
//N�� ���

/*
1) ������ �ʱ�ȭ �� �Է�
2) ���ϻ��� �� ����
3) �ε��ؼ� ����
4) ȭ�� ���
211207 git upload
		LinkiedList
*/
//1) ������ �ʱ�ȭ �� �Է�
void Create();

//2) ���ϻ��� �� ����
void Insert();

//3) �ε��ؼ� ����
void Load();

//4) ȭ�� ���
void Draw();

struct AUser
{
	int m_iIndex;
	char m_iName[16];
	int m_iKor;
	AUser* pNext;
	//AUser* pPrev;
};
AUser* g_pHeadUserList = 0;
AUser* g_pUserList = 0;
AUser* 

int main()
{
	struct AUser UserList[Byte] = {
		{1, "ȫ�浿", 35}, {2, "ȣ�̵Ѹ�", 45} };
	//���� ������ �� �ִ� lValue : https://comdori88-coding.tistory.com/6
	//int index = 1;
	//float iKor = 50.5f;
	FILE* fpdest = fopen("Samplebak.bak", "w");
	fwrite(UserList, 1, sizeof(AUser) * Byte, fpdest);

	/*FILE* fpWrite = fopen("Sample.txt", "w");
	{
		fprintf(fpWrite, "%s", "== Arim han ==");
		fprintf(fpWrite, "\n%s ", "User1");
		//fprintf(fpWrite, "%d %f", index, iKor);
		fclose(fpWrite);
	}

	char buffer[256] = { 0, };
	int indexRead;
	float iKorRead;

	FILE* fpRead = fopen("Sample.txt", "r");
	{
		fgets(buffer, 256, fpRead);
		fscanf(fpRead, "%s %d %f", buffer, &indexRead, &iKorRead);
		printf("\n%s %d %f", buffer, indexRead, iKorRead);
		fscanf(fpRead, "%s %d %f", buffer, &indexRead, &iKorRead);
		printf("\n%s %d %f", buffer, indexRead, iKorRead);
		fclose(fpRead);
	}*/
	return 0;
}

void Create();

void Insert();

void Load();

void Draw();



/*

int main()
{

	//2) ���ϻ��� �� ����
	AUser Userlist[MAX_USER];
	Userlist[0].m_iIndex = 0;
	Userlist[1].m_iIndex = 1;
	FILE* fpWrite = fopen("Sample.txt", "w");
	//������
	fwrite(&userlist, sizeof(AUser), MAX_USER, fpWrite);




	fclose(fpWrite);

	//3) �ε��ؼ� ����
	FILE* fpRead = fopen("Sample.txt", "r");
	char buffer[256] = { 0, };
	int valuetxt;
	fscanf(fpRead, "%c", buffer, &valuetxt);
	printf("%c", buffer, valuetxt);
	fclose(fpRead);


	return 0;
}*/