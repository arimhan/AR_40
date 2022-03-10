#include "World.h"
//#include "ObjectMgr.h"

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
		AObject2D* pObj = obj.get();
		if (pObj != nullptr) { pObj->Frame(); }
	}
	for (auto obj : m_NpcObj)
	{
		AObject2D* pObj = obj.get();
		if (pObj != nullptr) { pObj->Frame(); }
	}
	return true;
}
bool AWorld::Render()
{
	for (auto obj : m_UIObj)
	{
		AObject2D* pObj = obj.get();
		if (pObj != nullptr) { pObj->Render(); }
	}
	for (auto obj : m_NpcObj)
	{
		AObject2D* pObj = obj.get();
		if (pObj->m_bDead == false) { pObj->Render(); }
	}
	return true;
}
bool AWorld::Release()
{
	for (auto obj : m_UIObj)
	{
		obj->Release();
		obj = nullptr;
	}
	for (auto obj : m_ItemObj)
	{
		obj->Release();
		obj = nullptr;
	}
	for (auto obj : m_NpcObj)
	{
		obj->Release();
		obj = nullptr;
	}
	for (auto obj : m_MapObj)
	{
		obj->Release();
		obj = nullptr;
	}
	m_UIObj.clear();
	m_ItemObj.clear();
	m_NpcObj.clear();
	m_MapObj.clear();
	return true;
}
AWorld::AWorld() {}
AWorld::~AWorld() { Release(); }