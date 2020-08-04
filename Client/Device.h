#pragma once

#include "Include.h"

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	LPDIRECT3D9			m_p3D = nullptr;
	LPDIRECT3DDEVICE9   m_pDevice = nullptr;
	LPD3DXSPRITE		m_pSprite = nullptr;
	LPD3DXFONT			m_pFont = nullptr;

public:
	LPDIRECT3DDEVICE9		GetDevice() { return m_pDevice; }
	LPD3DXSPRITE			GetSprite() { return m_pSprite; }
	LPD3DXFONT				GetFont() { return m_pFont; }

public:
	HRESULT			InitDevice(void);
	void			Release(void);

	void			SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

	void			Render_Begin();
	void			Render_End(HWND hWnd = NULL);


private:
	CDevice();
	~CDevice();
};