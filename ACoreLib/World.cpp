#include "World.h"
AWorld* AWorld::m_pCurWorld = nullptr;
bool AWorld::Load(wstring saveFile)
{
	return true;
}
bool AWorld::Release()
{
	for (auto obj : m_UIObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_ItemObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	m_ItemObj.clear();
	m_UIObj.clear();
	return true;
}
AWorld::AWorld() {}
AWorld::~AWorld() {}