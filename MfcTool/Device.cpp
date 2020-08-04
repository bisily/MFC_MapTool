#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice()
{
}


CDevice::~CDevice()
{
}

HRESULT CDevice::IniDevice()
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"����̽� ���� ����");
		return E_FAIL;
	}

	DWORD		vp;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	// ����̽� ��ġ ����
	if (FAILED(m_p3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		vp,
		&d3dpp,
		&m_pDevice)))
	{
		AfxMessageBox(L"����̽� ��ġ ���� ����");
		return E_FAIL;
	}

	// ��������Ʈ ��ü ����
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		AfxMessageBox(L"��������Ʈ ��ü ���� ����");
		return E_FAIL;
	}

	// ��Ʈ ��ü ����
	D3DXFONT_DESCW		FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESCW));

	FontInfo.Height = 20;
	FontInfo.Width = 10;
	FontInfo.Weight = FW_HEAVY;
	FontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(FontInfo.FaceName, L"�ü�");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &FontInfo, &m_pFont)))
	{
		AfxMessageBox(L"��Ʈ ��ü ���� ����");
		return E_FAIL;
	}
	
	// Line ��ü ����
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		AfxMessageBox(L"���� ��ü ���� ����");
		return E_FAIL;
	}

	m_pLine->SetWidth(2);
	m_pLine->SetGLLines(FALSE); // TRUE = OpenGL, FALSE = Direct X
	return S_OK;
}

void CDevice::Release()
{
	m_pLine->Release();
	m_pFont->Release();
	m_pSprite->Release();
	m_pDevice->Release();
	m_p3D->Release();
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;		// ����� ���λ�����
	d3dpp.BackBufferHeight = WINCY;		// ����� ���� ������
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // ����� ����
	d3dpp.BackBufferCount = 1;		// ����� ����

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;		//  ��� ������(â)�� ������ ���ΰ�
	d3dpp.Windowed = TRUE;			// True(â���), FALSE(��üȭ�� ���)

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ��ü ȭ������ ����� �� ����� �ֻ����� �������� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �ֻ����� ������ ���̿� ������ ��� �� �������� ���� ����
}

void CDevice::Render_Begin()
{
	m_pDevice->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.f,
		0);

	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(HWND hWnd)
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, hWnd, NULL);
}
