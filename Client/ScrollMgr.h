#pragma once
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

private:
	CScrollMgr();
	~CScrollMgr();

public:
	void Update();

	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }

private:
	float		m_fScrollX = 0.f;
	float		m_fScrollY = 0.f;
	float		m_fOffSetX = WINCX / 2.f;
	float		m_fOffSetY = WINCY / 2.f;
};

