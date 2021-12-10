#include "Subject.h"

void ASubject::Set(int m_Kor)
{
	m_Kor = m_Kor;
};
int ASubject::GetKor()
{
	return m_Kor;
}
ASubject::ASubject()
{
	m_Kor = 0;
}
ASubject::~ASubject(){}