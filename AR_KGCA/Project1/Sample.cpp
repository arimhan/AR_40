#define _CRT_SECURE_NO_WARNINGS
#define Byte 16
#define List 20
#define MAX_USER 2
#include<stdio.h>
#include<string.h>

/*
1) 데이터 초기화 및 입력
2) 파일생성 후 저장
3) 로드해서 저장
4) 화면 출력
211206_FileIO_0~2까지 디버깅!
*/

struct AUser
{
	int m_iIndex;//[16];
	char m_iName [16] ;
	int m_iKor;
};//UserList[List];


int main()
{
	struct AUser UserList[Byte] = {
		{1, "홍길동", 35}, {2, "호이둘리", 45}};
	//식이 수정할 수 있는 lValue : https://comdori88-coding.tistory.com/6
	//int index = 1;
	//float iKor = 50.5f;
	FILE* fpdest= fopen("Samplebak.bak", "w");
	fwrite (UserList, 1, sizeof(AUser) * Byte, fpdest)

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




/*

int main()
{

	//2) 파일생성 후 저장
	AUser Userlist[MAX_USER];
	Userlist[0].m_iIndex = 0;
	Userlist[1].m_iIndex = 1;
	FILE* fpWrite = fopen("Sample.txt", "w");
	//블럭단위
	fwrite(&userlist, sizeof(AUser), MAX_USER, fpWrite);




	fclose(fpWrite);

	//3) 로드해서 저장
	FILE* fpRead = fopen("Sample.txt", "r");
	char buffer[256] = { 0, };
	int valuetxt;
	fscanf(fpRead, "%c", buffer, &valuetxt);
	printf("%c", buffer, valuetxt);
	fclose(fpRead);


	return 0;
}*/