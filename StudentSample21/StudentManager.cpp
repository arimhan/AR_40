#include "StudentManager.h"

AStudent* const AStudentManager::NewNode()
{
	AStudent* pUser = new AStudent();
	pUser->m_iIndex = g_iMaxUserCounter;
	pUser->m_iKor = rand() % 100;
	pUser->m_pNext = NULL; 
	return pUser;
}
void AStudentManager::Create()
{
	for (int iData = 0; iData < 1; iData++)
	{
		AddLink(NewNode());
	}
}

//연결리스트 출력
bool AStudentManager::FileSave()
{
	FILE* fpWrite = fopen("StudentSample.txt", "wb");
	int iCouner = g_iMaxUserCounter;
	fwrite(&iCouner, sizeof(int), 1, fpWrite);
	for (AStudent* user = g_pHeadUserList; user != NULL; user = user->m_pNext)
	{
		fwrite(user, sizeof(AStudent), 1, fpWrite);
	}
	fclose(fpWrite);
	return true;
}


void AStudentManager::DeleteAll()
{
	AStudent* m_pNext = g_pHeadUserList;
	while(m_pNext)
	{
		AStudent* pDeleteUser = m_pNext;
		m_pNext = pDeleteUser->m_pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		g_iMaxUserCounter--;
	}
	g_pHeadUserList = NULL;
}
int AStudentManager::Insert(FILE* fp)
{
	AStudent* pSaveEndNode = g_pEndUser;
	for (int iData = 0; iData < 2; iData++)
	{
		AddLink(NewNode());
	}
	fwrite(&g_iMaxUserCounter, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);
	for (AStudent* user = pSaveEndNode->m_pNext; user != NULL; user = user->m_pNext)
	{
		fwrite(user, sizeof(AStudent), 1, fp);
	}
	fclose(fp);
	fp = NULL;
	return g_iMaxUserCounter;
}
void AStudentManager::Load()
{
	FILE* fpRead = fopen("StudentSample.txt", "rb");
	int iCounerRead = 0;
	fread(&iCounerRead, sizeof(int), 1, fpRead);
	if (fpRead != NULL)
	{
		for (int iAdd = 0; iAdd < iCounerRead; iAdd++)
		{
			AStudent* pUser = new AStudent(0, 0);
			memset(pUser, 0, sizeof(AStudent));
			fread(pUser, sizeof(AStudent), 1, fpRead);
			pUser->m_pNext = 0;
			AddLink(pUser);
		}
		fclose(fpRead);
		fpRead = NULL;
	}
}
void AStudentManager::Draw()
{
	cout << *g_pHeadUserList;
}
void AStudentManager::AddLink(AStudent* const pUser)
{
	if (g_pHeadUserList == NULL)
	{
		g_pHeadUserList = pUser;
		g_pEndUser = pUser;
		g_iMaxUserCounter++;
		return;
	}
	g_pEndUser->m_pNext = pUser;
	g_pEndUser = pUser;
	g_iMaxUserCounter++;
}
ostream& operator << (ostream& os, const AStudentManager& manager)
{
	for (AStudent* user = manager.g_pHeadUserList; user != NULL; user = user->m_pNext)
	{
		cout << *user;
	}
	return os;
}