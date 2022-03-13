#include "Main.h"


void AMain::Init()
{
	//m_pBGMusic.Init("../../data/Sound/LovingCaliber.mp3");
	//m_pBGMusic.Play(true);
	m_IntroWorld.Init();
}

void AMain::Frame()
{
}

void AMain::Render()
{
}

void AMain::Release()
{

}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int iCmdShow)
{
	//�������� ����, �ν��Ͻ�(Game���� üũ)
	//m_iFPS, m_fSecondPerFrame, Timer, BeforeTime, FPSTimer, Counter�� ���� �ʱ���� �ʿ�
	MSG			winMsg;
	static int  iTickTrigger = 0;
	int         iTickCount=0;

	AGameEngine* pStart = new AGameEngine(hInstance, TEXT("KGCA_ARIMHAN"), TEXT("2DGAME_THE DODGE") ,600, 400);
	pStart->SetFrameRate(60);

	//AIntro Intro;
	AGameStateManager::Instance()->ChangeGameState(GS_INTRO);

	//Window ����
	if (!AGameEngine::GetEngine()->Initialize(iCmdShow))
		return FALSE;

	//Window ����
	while (1) 
	{
		if (PeekMessage(&winMsg, NULL, 0, 0, PM_REMOVE)) {
			if (winMsg.message == WM_QUIT)
				break;
			TranslateMessage(&winMsg);
			DispatchMessage(&winMsg);
		}
		else 
		{
			//GetTickCount �Լ��� ���� ���� Tick�� �޾ƿ� Frame�����̸� ����Ѵ�.
			iTickCount = GetTickCount();
			if (iTickCount > iTickTrigger) 
			{
				iTickTrigger = iTickCount + AGameEngine::GetEngine()->GetFrameDelay();

				//���ʴ�� ����, GetGameState(��Ʈ��/�÷��� �� ����üũ), ������ ���� ����üũ
				AGameStateManager::Instance()->Render();
				AGameStateManager::Instance()->GetGameState()->Update();

				AGameStateManager::Instance()->ChangeGameState(AGameStateManager::Instance()->GetGameState()->ChangeGameState());
			}
		}
	}
	AGameStateManager::Instance()->GameEnd();
	delete pStart;
	return (int)winMsg.wParam;
}

//���� �� ���ν���
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	ASample core;
//
//	if (core.SetWinClass(hInstance) == FALSE) return 1;
//	if (core.SetWindow(L"SelectClient Chat") == FALSE) return 1;
//	core.GameRun();
//	return 1;
//}