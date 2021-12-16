//
//
//void ACollegeStudent::Show()
//{
//	cout << "\tCollegeStudent ¼ºÀûÇ¥" << endl;
//	cout <<"\tIndex: " << m_iIndex << " " << "Type: " << m_iType << " " <<"Graphic: " << m_iGraphic << " "<<"Physic: " << m_iPhysics << " " 
//		<<"AI: " << m_iAI << " " <<"ToTal: " << m_iTotal << " "<<"Average: " << m_fAverage << " " <<endl<< endl;
//}
//
//void ACollegeStudent::Save()
//{
//	AStudent::Save();
//	char* pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(pData, &m_iGraphic, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(pData, &m_iPhysics, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(pData, &m_iAI, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	m_iBufferSize = m_iCurrentPosition;
//}
//
//void ACollegeStudent::Load()
//{
//	AStudent::Load();
//	char* pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(&m_iGraphic, pData, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(&m_iPhysics, pData, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	pData = &m_csBuffer[m_iCurrentPosition];
//	memcpy(&m_iAI, pData, sizeof(int));
//	m_iCurrentPosition += sizeof(int);
//
//	m_iTotal = m_iGraphic + m_iPhysics + m_iAI;
//	m_fAverage = m_iTotal / 3.0f;
//}
//
//void ACollegeStudent::SetData(int iIndex)
//{
//	m_iIndex = iIndex;
//	strcpy(m_csName, "none");
//	m_iGraphic = rand() % 100;
//	m_iPhysics = rand() % 100;
//	m_iAI = rand() % 100;
//	m_iTotal = m_iGraphic + m_iPhysics + m_iAI;
//	m_fAverage = m_iTotal / 3.0f;
//}
