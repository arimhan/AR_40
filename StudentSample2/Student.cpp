#include "Student.h"

template <typename T>
T AStudent::operator [] (int id)
{
	if (id == Index) return m_iIndex;
	if (id == Type) return m_iType;
	if (id == Total) return m_iTotal;
	return -1;
}
template <>
float AStudent::operator[] (int id)
{
	if (id == Average) return m_fAverage;
	return -1.0f;
}
void AStudent::Show()
{
	cout << "Index: " << operator[]<int>(Index) << " " << "Total: " << operator[]<int>(Total) << " " << "Average: " << operator[]<float>(Average) << " ";
	//cout << m_iIndex << " " << m_iTotal << " " << m_fAverage << " " << endl;
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

ostream& operator << (ostream& os, AStudent& data)
{
	os << data.m_iIndex << " " << data.m_iTotal << " " << data.m_fAverage << " " << endl;
	return os;
}