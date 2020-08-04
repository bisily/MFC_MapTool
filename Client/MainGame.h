#pragma once

#include "Include.h"

class CDevice;
class CSceneMgr;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	void	Progress();
	void	Render();
	void	Release();

private:
	CDevice*	m_pDevice = nullptr;
	CSceneMgr*	m_pScene = nullptr;

private:
	TCHAR		m_szFPS[MIN_STR]{};
	TCHAR		m_szMouse[MIN_STR]{};
	D3DXMATRIX	m_matTrans;
	D3DXMATRIX	m_matTrans2;
	float		m_fTime = 0.f;
	int			m_iCount = 0;

	HDC			m_hDC = nullptr;
};

