#include "StudentManager.h"

ANodeBox<AStudent>* const AStudentManager::NewNode()
{
	ANodeBox<AStudent>* pUser = new ANodeBox<AStudent>();
	return pUser;
}
void AStudentManager::Create()
{
	for (int iData = 0; iData < 1; iData++)
	{
		m_List.AddLink(NewNode());
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
ostream& operator << (ostream& os, const AStudentManager& manager)
{
	for (ANodeBox* pData = manager.g_pHeadUserList; pData != NULL; pData = pData->m_pNext)
	{
		pData->m_pData->Show();
	}
	return os;
}