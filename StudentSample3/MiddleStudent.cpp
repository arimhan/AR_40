#include "MiddleStudent.h"

void AMiddleStudent::Show()
{
	cout << "\n\tMiddleStudent ¼ºÀûÇ¥" << endl;
	cout <<"\tIndex: " << m_iIndex << " " << " Type: " << m_iType << " " <<" Kor: " << m_iKor << " " <<" Eng: " << m_iEng << " "
		<<" Mat: " << m_iMat << " " <<" Total: " << m_iTotal << " "<<" Average: " << m_fAverage << " " << endl;
}

void AMiddleStudent::Save()
{
	AStudent::Save();
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iKor, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iEng, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iMat, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	m_iBufferSize = m_iCurrentPosition;
}

void AMiddleStudent::Load()
{
	AStudent::Load();
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iKor, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iEng, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iMat, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	m_iTotal = m_iKor + m_iEng + m_iMat;
	m_fAverage = m_iTotal / 3.0f;
}

void AMiddleStudent::SetData(int iIndex)
{
	m_iIndex = iIndex;
	strcpy(m_csName, "none");
	m_iKor = rand() % 100;
	m_iEng = rand() % 100;
	m_iMat = rand() % 100;
	m_iTotal = m_iKor + m_iEng + m_iMat;
	m_fAverage = m_iTotal / 3.0f;
}
