#pragma once

#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	LPDIRECT3D9			m_p3D		= nullptr;
	LPDIRECT3DDEVICE9	m_pDevice	= nullptr;
	LPD3DXSPRITE		m_pSprite	= nullptr;
	LPD3DXFONT			m_pFont		= nullptr;
	LPD3DXLINE			m_pLine		= nullptr;

public:
	LPDIRECT3DDEVICE9	GetDevice() { return m_pDevice; }
	LPD3DXSPRITE		GetSprite() { return m_pSprite; }
	LPD3DXFONT			GetFont() { return m_pFont; }
	LPD3DXLINE			GetLine() { return m_pLine; }

public:
	HRESULT				IniDevice();
	void				Release();
	void				SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void				Render_Begin();
	void				Render_End(HWND hWnd = NULL);

private:
	CDevice();
	~CDevice();
};

