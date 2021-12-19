#include "Student.h"



AUser* AStudent::NewNode()
{
	AUser* pUser = new AUser(33, 77);
	pUser->m_Index = g_Maxcount;
	pUser->m_Kor = rand() % 100;
	pUser->pNext = NULL;
	return pUser;
}
void AStudent::DeleteAll()
{
	AUser* pNext = g_Start;
	while(pNext)
	{
		AUser* pDelUser = pNext;
		pNext = pDelUser->pNext;
		delete pDelUser;
		pDelUser = NULL;
		g_Maxcount--;
	}
	g_Start = NULL;
}
bool AStudent::SaveFile()
{
	FILE* fpWrite = fopen("Student1.txt", "wb");
	int iCouner = g_Maxcount;
	fwrite(&iCouner, sizeof(int), 1, fpWrite);
	for (AUser* user = g_Start; user != NULL; user = user->pNext)
	{
		fwrite(user, sizeof(AUser), 1, fpWrite);
	}
	fclose(fpWrite);
	return true;
}
int AStudent::SaveInsert(FILE* fp)
{
	AUser* pSaveEnd = g_End;
	for (int iData = 0; iData < 2; iData++)
	{
		AddLink(NewNode());
	}
	fwrite(&g_Maxcount, sizeof(int),1, fp);
	fseek(fp, 0, SEEK_END);
	for (AUser* user = pSaveEnd->pNext; user != NULL; user = user->pNext)
	{
		fwrite(user, sizeof(AUser),1, fp);
	}
	fclose(fp);
	fp = NULL;
	return g_Maxcount;
}
void AStudent::Create() 
{
	for (int iData = 0; iData < 1; iData++)
	{
		AddLink(NewNode());
	}
}
void AStudent::Load() 
{
	FILE* fpRead = fopen("Student1.txt", "rb");
	int iConRead = 0;
	fread(&iConRead, sizeof(int), 1, fpRead);

	if (fpRead != NULL)
	{
		for (int iAdd = 0; iAdd < iConRead; iAdd++)
		{
			AUser* pUser = new AUser(10, 99);
			memset(pUser, 0, sizeof(AUser));
			fread(pUser, sizeof(AUser), 1, fpRead);
			pUser->pNext = 0;
			AddLink(NewNode());
		}
		fclose(fpRead);
		fpRead = NULL;
	}
}
void AStudent::Draw() 
{
	for(AUser* user = g_Start; user != NULL; user= user->pNext)
	{
	printf("%d¹ø, %dÁ¡\n", user->m_Index, user->m_Kor);
	}
}
void AStudent::AddLink(AUser* pUser) 
{
	if (g_Start = NULL)
	{
		g_Start = pUser;
		g_End = pUser;
		g_Maxcount++;
		return;
	}
	g_End->pNext = pUser;
	g_End = pUser;
	g_Maxcount++;
}
