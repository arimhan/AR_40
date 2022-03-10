#pragma once
#include "Std.h"
template <class T, class S>
class ABaseMgr : public ASingleton<S>
{
public:
	friend class ASingleton<ABaseMgr>;
public:
	int		m_iIndex;
	ID3D11Device* m_pd3dDevice;
	map<wstring, std::shared_ptr<T> >  m_list;
public:
	wstring Splitpath(std::wstring path, std::wstring entry);
	virtual void	Set(ID3D11Device* pd3dDevice)
	{
		m_pd3dDevice = pd3dDevice;
	}
	virtual T* Load(wstring filename);
	T* GetPtr(wstring key);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	ABaseMgr();
public:
	~ABaseMgr();
};
template<class T, class S>
wstring ABaseMgr<T, S>::Splitpath(std::wstring path, std::wstring entry)
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
	if (entry.empty() == false)
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
		return (*iter).second.get();
	}
	return nullptr;
}
template<class T, class S>
T* ABaseMgr<T, S>::Load(wstring filename)
{
	wstring name = Splitpath(filename,L"");
	T* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	shared_ptr<T> pNewData = make_shared<T>();
	if (pNewData->Load(m_pd3dDevice, filename) == false)
	{
		return nullptr;
	}
	pNewData->m_csName = name;
	m_list.insert(make_pair(pNewData->m_csName, pNewData));
	m_iIndex++;
	return pNewData.get();
}
template<class T, class S>
bool	ABaseMgr<T, S>::Init()
{
	return true;
}
template<class T, class S>
bool	ABaseMgr<T, S>::Frame()
{
	return true;
}
template<class T, class S>
bool	ABaseMgr<T, S>::Render()
{
	return true;
}
template<class T, class S>
bool	ABaseMgr<T, S>::Release()
{
	for (auto data : m_list)
	{
		data.second->Release();		
	}
	m_list.clear();
	return true;
}
template<class T, class S>
ABaseMgr<T, S>::ABaseMgr()
{
	m_iIndex = 0;
}
template<class T, class S>
ABaseMgr<T,S>::~ABaseMgr()
{
	Release();
}