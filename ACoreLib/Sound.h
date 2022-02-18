#pragma once
#include "Std.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

class ASound
{
public:
	int				m_iIndex;
	FMOD::System*	m_pSystem = nullptr;
	FMOD::Sound*	m_pSound = nullptr;
	FMOD::Channel*	m_pChannel = nullptr;
	float			m_fVolume = 0.5f;
	wstring			m_szMsg;
	wstring			m_csName;
	TCHAR			m_szBuffer[256];
public:
	void Play(bool bLoop = false);	//실행, true받으면 실행!
	void PlayEffect();
	void Stop();	//정지
	void Paused();	//일시정지
	void VolumeUP(float fVolume = 0.1f);	//볼륨조절
	void VolumeDown(float fVolume = 0.1f);	//볼륨조절

public:
	void Set(FMOD::System* pSystem, wstring name, int iIndex);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	ASound();
	virtual ~ASound();
};
class ASoundMgr : public ASingleton<ASoundMgr>
{
	int			m_iIndex;
public:
	friend class ASingleton<ASoundMgr>;
	FMOD::System* m_pSystem = nullptr;
	map<wstring, ASound*> m_list;
public:
	ASound*		Load(string filename);
	ASound*		GetPtr(wstring key);
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	ASoundMgr();
	~ASoundMgr();
};
#define I_Sound ASoundMgr::Get()
