#include "Sample.h"
bool Sample::Init()
{
	return true;
}
bool Sample::Frame() 
{
	return true;
}
bool Sample::Render() 
{
	return true;
}
bool Sample::Release() 
{
	return true;
}
Sample::Sample() {};
Sample::~Sample() {};
SIMPLE_RUN();
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	Sample core;
//
//	if (core.SetWinClass(hInstance) == FALSE) return 1;
//	if (core.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
//	core.GameRun();
//	return 1;
//}