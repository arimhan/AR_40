#include "Play.h"
#define LIFECOUNT 3


APlay::APlay() 
{
	flag = GS_WAIT;
	// 초기화 
	//_iLevel = 1;
	//_iLive = LIFECOUNT;
	//_iScore = 0;
	Init();
	GameInit();
	LoadMap();
	//_GameState = 1;
}
APlay::~APlay() {}

void APlay::Init()
{
	//Start버튼 누르면 존 이동
	

}
void APlay::GameInit(){}
void APlay::Update() {}
void APlay::Render(HDC hdc) {}
GameState APlay::ChangeGameState() { return flag; };
void APlay::CheckCollision() {}
void APlay::CheckCollision_Enemy() {}
void APlay::DrawMap(HDC hdc) {}
void APlay::LoadMap() {}

