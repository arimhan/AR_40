#pragma once
#include "Std.h"

template<class T, class S>
class ABaseMgr :public ASingleton<S>
{
public:
	friend class ASingleton<ABaseMgr>;
public:
	int					m_iIndex;
	ID3D11Device*		m_pd3dDevice;
	map<wstring, T*>	m_list;
public:
	wstring Splitpath(wstring path, wstring entry);
	virtual void Set(ID3D11Device* pd3dDevice)
	{
		m_pd3dDevice = pd3dDevice;
	}

	T*		GetPtr(wstring key);
	T*		Load(wstring filename);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	ABaseMgr();
	~ABaseMgr();
};
template<class T, class S>
wstring ABaseMgr<T, S>::Splitpath(wstring path, wstring entry)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };

	wstring fullpathname = path;
	_tsplitpath_s(fullpathname.c_str(), Dirve, Dir, FileName, FileExt);
	wstring name = FileName;
	name += FileExt;
	if(entry.empty() == false)
	{
		name += entry;
	}
	return name;
}
template<class T, class S>
T* ABaseMgr<T, S>::GetPtr(wstring key)
{
	auto iter = m_list.find(key);
	if (iter != m_list.end())
	{
		return (*iter).second;
	}
	return nullptr;
}
template<class T, class S>
T* ABaseMgr<T, S>::Load(wstring Filename)
{
	wstring name = Splitpath(Filename, L"");
	T* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	pData = new T;
	if (pData->Load(m_pd3dDevice, Filename) == false)
	{
		delete pData;
		return nullptr;
	}
	pData->m_csName = name;
	m_list.insert(make_pair(pData->m_csName, pData));
	m_iIndex++;
	return pData;
}
template<class T, class S>
bool ABaseMgr<T, S>::Init() { return true; }
template<class T, class S>
bool ABaseMgr<T, S>::Frame() { return true; }
template<class T, class S>
bool ABaseMgr<T, S>::Render() { return true; }
template<class T, class S>
bool ABaseMgr<T, S>::Release() 
{ 
	for (auto data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
	return true; 
}
template<class T, class S>
ABaseMgr<T, S>::ABaseMgr() {}
template<class T, class S>
ABaseMgr<T, S>::~ABaseMgr() { Release(); }