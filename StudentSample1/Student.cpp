#include "Student.h"


int& AStudent::operator [] (int id)
{
	if (id == 0) return m_iIndex;
	else if (id == 1) return m_iKor;
	return m_iKor;
}
ostream& operator << (ostream& os, AStudent& data)
{
	os << "idx: " <<data[0] << "  kor: " << data[1] << endl;
	return os;
}