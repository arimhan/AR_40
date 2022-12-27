#pragma once
#include "Std.h"
#include <strsafe.h>

template <class T, class S>
class ABaseMgr : public ASingleton<S>
{
public:
	friend class ASingleton<ABaseMgr>;
public:
	int							m_iIndex;
	ID3D11Device*				m_pd3dDevice;
	ID3D11DeviceContext*		m_pContext;

	map<wstring, shared_ptr<T>>		m_list;
public:
	wstring			Splitpath(wstring path, wstring entry);
	virtual void	Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext = nullptr);
	virtual T*		Load(wstring filename);
	T*				GetPtr(wstring key);
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	ABaseMgr();
public:
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
	if (entry.empty() == false)
	{
		name += entry;
	}
	return name;
}

template <class T, class S>
void ABaseMgr<T, S>::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext )
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
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
	wstring name = Splitpath(filename, L"");
	T* pData = GetPtr(name);
	if (pData != nullptr) { return pData; }
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
bool	ABaseMgr<T, S>::Init() { return true; }
template<class T, class S>
bool	ABaseMgr<T, S>::Frame() { return true; }
template<class T, class S>
bool	ABaseMgr<T, S>::Render() { return true; }

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
ABaseMgr<T, S>::ABaseMgr() { m_iIndex = 0; }
template<class T, class S>
ABaseMgr<T, S>::~ABaseMgr() { Release(); }
namespace A
{
	static void DisplayErrorBox(const WCHAR* lpszFunction)
	{
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
			(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf,
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s failed with error %d: %s"),
			lpszFunction, dw, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
	}

	static DWORD LoadAllPath(const TCHAR* argv, std::vector<std::wstring>& list)
	{
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		TCHAR szDir[MAX_PATH];
		size_t length_of_arg;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		DWORD dwError = 0;

		StringCchLength(argv, MAX_PATH, &length_of_arg);
		if (length_of_arg > (MAX_PATH - 3))
		{
			return(-1);
		}
		StringCchCopy(szDir, MAX_PATH, argv);
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

		hFind = FindFirstFile(szDir, &ffd);

		if (INVALID_HANDLE_VALUE == hFind)
		{
			DisplayErrorBox(TEXT("FindFirstFile"));
			return dwError;
		}
		do 
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

			}
			else
			{
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
				std::wstring path = argv;
				path += L"/";
				path += ffd.cFileName;
				list.push_back(path);
			}

		} while (FindNextFile(hFind, &ffd) != 0);

		dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
		{
			DisplayErrorBox(TEXT("FineFirstFile"));
		}
		FindClose(hFind);
		return dwError;
	} 
}
