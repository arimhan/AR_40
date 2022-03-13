#include "Intro.h"
#include "SoundMgr.h"

ASound* pSound;
ASoundMgr* pSoundMgr;
ACore* acore;

AIntro::AIntro()
{
	//���ο��� ���� �� ���� ���� ������ ��.
	// Frame������� ó��
	ATimer at;
	AWindow aw;
	at.m_fSecondPerFrame = 0.0f;
	at.m_fTimer = 0.0f;
	at.m_dwBeforeTime = timeGetTime();

	GetClientRect(aw.m_hWnd, &aw.m_rtClient);
	GetWindowRect(aw.m_hWnd, &aw.m_rtWindow);
	g_rtClient = aw.m_rtClient;

	acore->CoreInit();
	I_Sound.Init();
	I_Sound.Frame();


	//pSoundMgr->Frame();
	//pSound->Frame();
	//I_Sound.Init();
}
AIntro::~AIntro()
{}
void AIntro::Init()
{
	HINSTANCE hInstance = AGameEngine::GetEngine()->GetInstance();
	flag = GS_WAIT;
	ASound* pSound = I_Sound.Load("../../data/Sound/Munn.mp3");
	m_pBGMusic = I_Sound.Load("../../data/Sound/Munn.mp3");
	m_pBGMusic->Play(true);
}

bool AIntro::Frame()
{
	return true;
}

bool AIntro::Release()
{
	return true;
}

void AIntro::Update()//(string filename)
{
	//if(//Start ��ư ������ ���� ����)
	
}

void AIntro::Render(HDC hdc)
{
}

GameState AIntro::ChangeGameState()
{
	return GameState();
}

bool AIntro::CreateModelType()
{
	return true;
}

bool AIntro::Load(wstring file)
{
	return true;
}
