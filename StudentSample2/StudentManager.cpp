#include "StudentManager.h"

ANodeBox<AStudent>* const AStudentManager::NewNode()
{
	ANodeBox<AStudent>* pNodeBox = new ANodeBox<AStudent>();
	int iType = rand() % 3;
	AStudent* pObject = nullptr;
	if (iType == 0)
		pObject = new AMiddleStudent();
	else if (iType == 1)
		pObject = new AHighStudent();
	else if (iType == 2)
		pObject = new ACollegeStudent();
	else
		cout << "error : StudentManager_NewNode";

	pObject->SetData(m_List.m_iNumNode);
	pNodeBox->m_pData = pObject;

	return pNodeBox;
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
	if (m_FileIO.CreateFile(pFileName))
	{
		m_FileIO.Write(&m_List.m_iNumNode, sizeof(int));
		for (ANodeBox<AStudent>* pData = m_List.GetHead(); pData != NULL; pData = pData->m_pNext)
		{
			pData->m_pData->Save();
			m_FileIO.Write(&pData->m_pData->m_iType, sizeof(int));
			m_FileIO.Write(&pData->m_pData->m_iBufferSize, sizeof(int));
			m_FileIO.Write(&pData->m_pData->m_csBuffer, pData->m_pData->m_iBufferSize);
		}
		m_FileIO.CloseFile();
	}
	return true;
}

void AStudentManager::Load(const char* pFileName)
{
	if (m_FileIO.OpenFile(pFileName))
	{
		int iCounerRead = 0;
		m_FileIO.Read(&iCounerRead, sizeof(int));
		for (int iAdd = 0; iAdd < iCounerRead; iAdd++)
		{
			ANodeBox<AStudent>* pData = new ANodeBox<AStudent>();
			int iType = -1;
			m_FileIO.Read(&iType, sizeof(int));

			if (iType == 1)
				pData->m_pData = new AMiddleStudent();
			else if (iType == 2)
				pData->m_pData = new AHighStudent();
			else if (iType == 3)
				pData->m_pData = new ACollegeStudent();
			else
				cout << "error : StudentManager_Load";

			m_FileIO.Read(&pData->m_pData->m_iBufferSize, sizeof(int));
			m_FileIO.Read(&pData->m_pData->m_csBuffer, pData->m_pData->m_iBufferSize);

			pData->m_pData->Load();
			m_List.AddLink(pData);
		}
		m_FileIO.CloseFile();
	}
}
void AStudentManager::Draw()
{
	cout << m_List.GetHead();
}
void AStudentManager::DeleteAll()
{
	m_List.DeleteAll();
}
ostream& operator << (ostream& os, AStudentManager& manager)
{
	for (ANodeBox<AStudent>* pData = manager.m_List.GetHead(); pData != NULL; pData = pData->m_pNext)
	{
		if(pData->m_pData != nullptr)
		{ 
			pData->m_pData->Show();
		}
	}
	return os;
}