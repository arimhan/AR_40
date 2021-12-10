#include "StudentManager.h"

AStudent* const AStudentManager::NewNode()
{
	AStudent* pUser = new AStudent();
	pUser->m_iIndex = g_Maxcount;
	pUser->m_iKor = rand() % 100;
	pUser->pNext = NULL;
	return pUser;
}
void AStudentManager::AddLink(AStudent* const pUser)
{
	if (g_Start == NULL)
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
void AStudentManager::Create()
{
	for (int iData = 0; iData < 1; iData++)
	{
		AddLink(NewNode());
	}
}
void AStudentManager::DeleteAll()
{
	AStudent* pNext = g_Start;
	while (pNext)
	{
		AStudent* pDeleteUser = pNext;
		pNext = pDeleteUser->pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		g_Maxcount--;
	}
	g_Start = NULL;
}
int AStudentManager::SaveInsert(FILE* fp)
{
	AStudent* pSaveEndNode = g_End;
	for (int iData = 0; iData < 2; iData++)
	{
		AddLink(NewNode());
	}

	fwrite(&g_Maxcount, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);
	for (AStudent* user = pSaveEndNode->pNext; user != NULL; user = user->pNext)
	{
		fwrite(user, sizeof(AStudent), 1, fp);
	}
	fclose(fp);
	fp = NULL;
	return g_Maxcount;
}
void AStudentManager::Load()
{
	FILE* fpRead = fopen("Sample.txt", "rb");
	int iCounterRead = 0;
	fread(&iCounterRead, sizeof(int), 1, fpRead);

	if (fpRead != NULL)
	{
		for (int iAdd = 0; iAdd < iCounterRead; iAdd++)
		{
			AStudent* pUser = new AStudent(30, 40);
			memset(pUser, 0, sizeof(AStudent));
			fread(pUser, sizeof(AStudent), 1, fpRead);
			pUser->pNext = 0;
			AddLink(pUser);
		}
		fclose(fpRead);
		fpRead = NULL;
	}
}
bool AStudentManager::SaveFile()
{
	FILE* fpWrite = fopen("Sample.txt", "wb");
	int iCouner = g_Maxcount;
	fwrite(&iCouner, sizeof(int), 1, fpWrite);
	for (AStudent* user = g_Start; user != NULL; user = user->pNext)
	{
		fwrite(user, sizeof(AStudent), 1, fpWrite);
	}
	fclose(fpWrite);
	return true;
}

void AStudentManager::Draw()
{
	std::cout << *g_Start;
	//for (AStudent* user = g_Start; user != NULL; user = user->pNext)
	//{
	//	printf("%d %d\n", user->m_iIndex, user->m_iKor);
	//}
}

ostream& operator<< (ostream& os, const AStudentManager& manager)
{
	for (AStudent* user = manager.g_Start; user != NULL; user = user->pNext)
	{
		cout << *user;
	}
	return os;
}