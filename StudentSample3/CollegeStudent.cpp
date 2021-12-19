#include "CollegeStudent.h"

void ACollegeStudent::Show()
{
	cout << "\n\tCollegeStudent 성적표" << endl;
	cout << "\tIndex:" << m_iIndex << "번" << " Type: " << m_iType << "(College)" << " Graphic: " << m_iGraphic << "점" << " Physic: " << m_iPhysics << "점"
		<< " AI: " << m_iAI << "점" << " ToTal: " << m_iTotal << "점" << " Average: " << m_fAverage << "점" << endl;
}

void ACollegeStudent::Save()
{
	AStudent::Save();
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iGraphic, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iPhysics, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iAI, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	m_iBufferSize = m_iCurrentPosition;
}

void ACollegeStudent::Load()
{
	AStudent::Load();
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iGraphic, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iPhysics, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iAI, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	m_iTotal = m_iGraphic + m_iPhysics + m_iAI;
	m_fAverage = m_iTotal / 3.0f;
}

void ACollegeStudent::SetData(int iIndex)
{
	m_iIndex = iIndex;
	strcpy(m_csName, "none");
	m_iGraphic = rand() % 100;
	m_iPhysics = rand() % 100;
	m_iAI = rand() % 100;
	m_iTotal = m_iGraphic + m_iPhysics + m_iAI;
	m_fAverage = m_iTotal / 3.0f;
}
