#define _CRT_SECURE_NO_WARNINGS
#define MaxCount 20
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "Student.h"
#include "Student.h"
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



void main()//int argc, char* argv[]) cmd나 디버그에서 값을 인자로 받고 싶으면 다음과 같이 처리
{
	FILE* fp = Create();
	fclose(fp);
	AllDelete();
	Load();
	Draw(g_iMaxUserCounter);
	AllDelete();
}

