#pragma once

#define MAX_VIRTURAL_KEY 0xFF

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

public:
	bool	GetKeyProssing(int iKey);
	bool	GetKeyDown(int iKey);
	bool	GetKeyUp(int iKey);

public:
	void	Update();

private:
	CKeyMgr();
	~CKeyMgr();

private:
	bool	m_bKey[MAX_VIRTURAL_KEY];
};

#define KEY_DOWN(Key) CKeyMgr::GetInstance()->GetKeyDown(Key)
#define KEY_UP(Key) CKeyMgr::GetInstance()->GetKeyUp(Key)
#define KEY_PRESSING(Key) CKeyMgr::GetInstance()->GetKeyProssing(Key)
