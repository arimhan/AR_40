#include "IntroWorld.h"
#include "Input.h"
bool AIntroWorld::Init() 
{
	//m_pBackGroundMusic->Play(true);
	return true; 
}
bool AIntroWorld::Frame() 
{
	m_pBackGroundMusic->Frame();
	return true; 
}
bool AIntroWorld::Render() { return true; }
bool AIntroWorld::Release() { return true; }
bool AIntroWorld::Load(wstring file)
{
	//����ȭ�鿡���� �� ������ �������� ~
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/NewHopeClub.MP3");
	AObject2D* pObj = new AObject2D;
	pObj->Init();
	return true;
}
