#include "Sample.h"
bool Sample::Init()
{
	//int ObjList = 12; //사각형 정점 6개, X 2 = 12개 
	for (int iObj = 0; iObj < 12; iObj++)
	{
		ADxObject  obj;
		obj.Init();

		if (obj.Create(m_pd3dDevice, m_pImmediateContext, AVector2(-100 * iObj, iObj * 50), 400, 30))
		{
			m_ObjectList.push_back(obj);
		}
	}
	return true;
}
bool Sample::Frame() 
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Frame();
	}
	return true;
}
bool Sample::Render() 
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Render();
	}
	return true;
}
bool Sample::Release() 
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Release();
	}
	return true;
}
Sample::Sample() {};
Sample::~Sample() {};
//SIMPLE_ARUN();
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample core;

	if (core.SetWinClass(hInstance) == FALSE) return 1;
	if (core.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
	core.GameRun();
	return 1;
}