#include "SoundMgr.h"

void ASound::Set(FMOD::System* pSystem, wstring name, int iIndex)
{
	m_pSystem = pSystem;
	m_csName = name;
	m_iIndex = iIndex;
}
void ASound::Play(bool bLoop)
{
	//bPlay가 ture일 경우 재생
	bool bPlay = false;
	//(channel)채널: 플레이 되는 사운드의 제어
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&bPlay);
	}
	if (bPlay == false)
	{
		FMOD_RESULT ret = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		//Sound* sound, ChannelGroup* channelgroup, bool paused, Channel** channel
		if (ret == FMOD_OK)
		{
			if (bLoop)
				m_pChannel->setMode(FMOD_LOOP_NORMAL);
			else
				m_pChannel->setMode(FMOD_LOOP_OFF);
		}
	}
}
void ASound::PlayEffect()
{
	//채널은 플레이 되는 사운드의 제어를 담당
	FMOD::Channel* pChannel = nullptr;
	FMOD_RESULT ret = m_pSystem->playSound(m_pSound, nullptr, false, &pChannel);
	if (ret == FMOD_OK)
	{
		//이펙트 사운드 작업
	}
}
void ASound::Stop()
{
	if (m_pChannel != nullptr)
	{
		m_pChannel->stop();
	}
}
void ASound::Paused()
{
	bool bPlay = false;
	m_pChannel->isPlaying(&bPlay);
	if (bPlay)
	{
		bool paused;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}
void ASound::VolumeUP(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume + fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min(1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}
void ASound::VolumeDown(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume - fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min(1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}
bool ASound::Init()
{
	//FMOD::System* m_pSystem = nullptr;
	//FMOD::Sound* m_pSound = nullptr;
	//FMOD::Channel* m_pChannel = nullptr;
	//FMOD_RESULT ret;
	//ret = FMOD::System_Create(&m_pSystem);
	//ret = m_pSystem->init(32,FMOD_INIT_NORMAL, 0);
	////int maxchannels = 32 , FMOD_INITFLAGS flags =FMOD_INIT_NORMAL , void* extradriverdata
	return true;
}
bool ASound::Frame()
{
	if (m_pSound == nullptr || m_pChannel == nullptr) return true;

	unsigned int ms = 0;
	unsigned int size = 0;
	m_pSound->getLength(&size, FMOD_TIMEUNIT_MS);
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);

	_stprintf_s(m_szBuffer, _T("PlayTime:[%02d:%02d:%02d] [%02d:%02d:%02d]"),
		size / 1000 / 60, size / 1000 % 60, size / 10 % 60,
		ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 60);
	//사운드 파일을 한 번에 로딩 or 스트리밍 -> update 반드시 호출!
	//m_pSystem->update(); ->soundmgr frame에서 진행함
	return true;
}
bool ASound::Render() { return true; }
bool ASound::Release()
{
	if (m_pSound)
	{
		//m_pSystem->close(); soundmgr release에서 진행
		m_pSystem->release();
		m_pSound = nullptr;
	}
	return true;
}
ASound::ASound() {}
ASound::~ASound() {}

//----------------------------------------SoundMgr
ASound* ASoundMgr::Load(string filename)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };

	wstring fullpathname = to_mw(filename);
	_tsplitpath_s(fullpathname.c_str(), Dirve, Dir, FileName, FileExt);
	wstring name = FileName;
	name += FileExt;

	for (auto data : m_list)
	{
		if (data.second->m_csName == name)
		{
			return data.second.get();
		}
	}
	std::shared_ptr<ASound> pSound = std::make_shared<ASound>();
	//ASound* pSound = new ASound;
	FMOD_RESULT ret = m_pSystem->createSound(
		filename.c_str(), FMOD_DEFAULT, 0, &pSound->m_pSound);
	//(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, Sound** sound)

	if (ret != FMOD_OK)
	{
		return nullptr;
	}
	m_list.insert(make_pair(name, pSound));
	pSound->Set(m_pSystem, name, m_iIndex);
	m_iIndex++;
	return pSound.get();
}
ASound* ASoundMgr::GetPtr(wstring key)
{
	auto iter = m_list.find(key);
	if (iter != m_list.end())
	{
		return (*iter).second.get();
	}
	return nullptr;
}
bool ASoundMgr::Init()
{
	FMOD_RESULT ret;
	ret = FMOD::System_Create(&m_pSystem);
	ret = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	//int maxchannels, FMOD_INITFLAGS flags, void* extradriverdata
	return true;
}
bool ASoundMgr::Frame()
{
	m_pSystem->update();
	return true;
}
bool ASoundMgr::Render() { return true; }
bool ASoundMgr::Release()
{
	for (auto data : m_list)
	{
		data.second->Release();
		//delete data.second.get();
	}
	m_list.clear();

	if (m_pSystem)
	{
		m_pSystem->close();
		m_pSystem->release();
	}
	m_pSystem = nullptr;
	return true;
}
ASoundMgr::ASoundMgr() { m_iIndex = 0; }
ASoundMgr::~ASoundMgr() { Release(); }
