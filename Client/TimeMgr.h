#pragma once

#include "Include.h"

class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;
	LARGE_INTEGER		m_CpuTick;

private:
	float				m_fTime = 0.f;

public:
	float				GetTime();
	void				InitTime();
	void				SetTime();

private:
	CTimeMgr();
	~CTimeMgr();
};

