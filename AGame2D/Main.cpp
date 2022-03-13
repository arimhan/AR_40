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
	//지역변수 선언, 인스턴스(Game상태 체크)
	//m_iFPS, m_fSecondPerFrame, Timer, BeforeTime, FPSTimer, Counter값 전부 초기셋팅 필요
	MSG			winMsg;
	static int  iTickTrigger = 0;
	int         iTickCount=0;

	AGameEngine* pStart = new AGameEngine(hInstance, TEXT("KGCA_ARIMHAN"), TEXT("2DGAME_THE DODGE") ,600, 400);
	pStart->SetFrameRate(60);

	//AIntro Intro;
	AGameStateManager::Instance()->ChangeGameState(GS_INTRO);

	//Window 생성
	if (!AGameEngine::GetEngine()->Initialize(iCmdShow))
		return FALSE;

	//Window 실행
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
			//GetTickCount 함수를 통해 현재 Tick을 받아와 Frame딜레이를 출력한다.
			iTickCount = GetTickCount();
			if (iTickCount > iTickTrigger) 
			{
				iTickTrigger = iTickCount + AGameEngine::GetEngine()->GetFrameDelay();

				//차례대로 렌더, GetGameState(인트로/플레이 등 상태체크), 변경할 게임 상태체크
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

//원래 윈 프로시저
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	ASample core;
//
//	if (core.SetWinClass(hInstance) == FALSE) return 1;
//	if (core.SetWindow(L"SelectClient Chat") == FALSE) return 1;
//	core.GameRun();
//	return 1;
//}