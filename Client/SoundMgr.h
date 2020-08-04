#pragma once

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNEL_ID { CHANNEL_BGM, CHANNEL_PLAYER, CHANNEL_DRUMMOVE, CHANNEL_ENEMY, CHANNEL_EFFECT, CHANNEL_BOMB, CHANNEL_DRIVE, CHANNEL_END };

public:
	void Initialize();
	void Update();
	void Release();

public:
	void LoadSoundFile();
	void PlayerSound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void PlayBGMEx(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopSoundAll();


private:
	CSoundMgr();
	~CSoundMgr();

private:
	FMOD_SYSTEM*	m_pSystem;
	FMOD_CHANNEL*	m_pChannelArr[CHANNEL_END];

	map<const TCHAR*, FMOD_SOUND*>		m_MapSound;
};

