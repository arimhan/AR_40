#include "StudentManager.h"

ANodeBox* const AStudentManager::NewNode()
{
	ANodeBox* pUser = new ANodeBox(g_iMaxUserCounter);
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
bool AStudentManager::FileSave(const char* pFileName)
{
	FILE* fpWrite = fopen(pFileName, "wb");
	int iCouner = g_iMaxUserCounter;
	fwrite(&iCouner, sizeof(int), 1, fpWrite);
	for (ANodeBox* pData = g_pHeadUserList; pData != NULL; pData = pData->m_pNext)
	{
		pData->m_pData->Save();
		fwrite(&pData->m_pData->m_iType, sizeof(int), 1, fpWrite);
		fwrite(&pData->m_pData->m_iBufferSize, sizeof(int), 1, fpWrite);
		fwrite(pData->m_pData->m_csBuffer, pData->m_pData->m_iBufferSize, 1, fpWrite);
	}
	fclose(fpWrite);
	return true;
}
void AStudentManager::DeleteAll()
{
	ANodeBox* m_pNext = g_pHeadUserList;
	while(m_pNext)
	{
		ANodeBox* pDeleteUser = m_pNext;
		m_pNext = pDeleteUser->m_pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		g_iMaxUserCounter--;
	}
	g_pHeadUserList = NULL;
}
void AStudentManager::Load(const char* pFileName)
{
	FILE* fpRead = fopen(pFileName, "rb");
	int iCounerRead = 0;
	fread(&iCounerRead, sizeof(int), 1, fpRead);
	if (fpRead != NULL)
	{
		for (int iAdd = 0; iAdd < iCounerRead; iAdd++)
		{
			ANodeBox* pData = new ANodeBox();
			memset(pData, 0, sizeof(ANodeBox));
			int iType = -1;
			fread(&iType, sizeof(int), 1, fpRead);
			
			if (iType == 1)
				pData->m_pData = new AMiddleStudent();
			else if (iType == 2)
				pData->m_pData = new AHighStudent();
			else if (iType == 3)
				pData->m_pData = new ACollegeStudent();
			else
				cout << "error : StudentManager_Load";

			fread(&pData->m_pData->m_iBufferSize, sizeof(int), 1, fpRead);
			fread(pData->m_pData->m_csBuffer, pData->m_pData->m_iBufferSize, 1, fpRead);

			pData->m_pData->Load();
			AddLink(pData);
		}
		fclose(fpRead);
		fpRead = NULL;
	}
}
void AStudentManager::Draw()
{
	cout << *g_pHeadUserList;
}
void AStudentManager::AddLink(ANodeBox* const pUser)
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
	for (ANodeBox* pData = manager.g_pHeadUserList; pData != NULL; pData = pData->m_pNext)
	{
		pData->m_pData->Show();
	}
	return os;
}