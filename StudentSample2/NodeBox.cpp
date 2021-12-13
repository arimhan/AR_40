#include "NodeBox.h"

AStudent* ANodeBox::NewData(int iIndex)
{
	int iType = rand() % 3;
	AStudent* pUser = nullptr;
	if (iType == 0)
		pUser = new AMiddleStudent();
	else if (iType == 1)
		pUser = new AHighStudent();
	else if (iType == 2)
		pUser = new ACollegeStudent();
	else
		cout << "error : NodeBox _ NewData";
	pUser->SetData(iIndex);
	return pUser;
}
ostream& operator << (ostream& os, ANodeBox& data)
{
	os << *data.m_pData;
	return os;
}
ANodeBox::ANodeBox()
{
	m_pData = nullptr;
}
ANodeBox::ANodeBox(int iIndex)
{
	m_pData = NewData(iIndex);
}
ANodeBox::~ANodeBox()
{
	delete m_pData;
}