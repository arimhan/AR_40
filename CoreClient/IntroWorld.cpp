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
	//시작화면에서는 이 음악이 나오도록 ~
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/NewHopeClub.MP3");
	AObject2D* pObj = new AObject2D;
	pObj->Init();
	return true;
}
