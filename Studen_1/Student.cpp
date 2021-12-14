#include "Student.h"

template <class T>
T AStudent::operator [] (int id)
{
	if (id == Index) return m_iIndex;
	if (id == Type) return m_iType;
	if (id == Total) return m_iTotal;
	return -1;
}
template <>
float AStudent::operator [] (int id)
{
	if (id == Average) return m_fAverage;
	return -1.0f;
}

void AStudent::Show()
{

}
void AStudent::Save() {}
void AStudent::Load() {}
void AStudent::SetData() {}

ostream& operator << (ostream& os, AStudent& data)
{
	cout << "Index: " << data.m_iIndex << "Total: " << data.m_iTotal << "Average: " << data.m_fAverage << endl;
}