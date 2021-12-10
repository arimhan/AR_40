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
void AStudent::Create()
{
	for (int iData = 0; iData < 1; iData++)
	{
		AddLink(NewNode());
	}
}
void AStudent::DeleteAll()
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
int AStudent::SaveInsert(FILE* fp)
{
	return g_Maxcount;
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

void AStudent::Draw()
{
	for (AUser* user = g_Start; user != NULL; user = user->pNext)
	{
		printf("%d %d\n", user->m_iIndex, user->m_iKor);
	}
}