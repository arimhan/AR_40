#include "Student.h"

void AStudent::Show()
{
	cout << m_iIndex << " " << m_iTotal << " " << m_fAverage << " " << endl;
}

void AStudent::Save()
{
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iIndex, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(pData, &m_iType, sizeof(int));
	m_iCurrentPosition += sizeof(int);
}
void AStudent::Load()
{
	char* pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iIndex, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);

	pData = &m_csBuffer[m_iCurrentPosition];
	memcpy(&m_iType, pData, sizeof(int));
	m_iCurrentPosition += sizeof(int);
}
void AStudent::SetData(int iIndex)
{
	m_iIndex = iIndex;
	m_iTotal = 0;
	strcpy(m_csName, "none");
	m_fAverage = m_iTotal / 3.0f;
}
int& AStudent::operator[] (int id)
{
	if (id == 0) return m_iIndex;
	return m_iTotal;
}
ostream& operator << (ostream& os, AStudent& data)
{
	os << data.m_iIndex << " " << data.m_iTotal << " " << data.m_fAverage << " " << endl;
	return os;
}