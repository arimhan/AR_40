#include "World.h"
AWorld* AWorld::m_pCurWorld = nullptr;
bool AWorld::Load(wstring saveFile)
{
	return true;
}
bool AWorld::Init()
{
	return true;
}
bool AWorld::Frame()
{
	for (auto obj : m_UIObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr) { pObj->Frame(); }
	}
	for (auto obj : m_NpcObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr) { pObj->Frame(); }
	}
	return true;
}
bool AWorld::Render()
{
	for (auto obj : m_UIObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr) { pObj->Render(); }
	}
	for (auto obj : m_NpcObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr) { pObj->Render(); }
	}
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
	for (auto obj : m_NpcObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_MapObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	m_UIObj.clear();
	m_ItemObj.clear();
	m_NpcObj.clear();
	m_MapObj.clear();
	return true;
}
AWorld::AWorld() {}
AWorld::~AWorld() {}