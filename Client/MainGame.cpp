#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"

CMainGame::CMainGame()
	: m_pDevice(CDevice::GetInstance())
	, m_pScene(CSceneMgr::GetInstance())
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	if (FAILED(m_pDevice->InitDevice()))
	{
		ERR_MSG(L"MainGame Device FAILED");
		return E_FAIL;
	}

	CTimeMgr::GetInstance()->InitTime();
	m_pScene->SetScene(SC_LOGO);

	ShowCursor(FALSE);

	return S_OK;
}

void CMainGame::Progress()
{
	CTimeMgr::GetInstance()->SetTime();
	CKeyMgr::GetInstance()->Update();
	CSoundMgr::GetInstance()->Update();

	m_pScene->Progress();

	D3DXMatrixTranslation(&m_matTrans, 600.f, 50.f, 0.f);

	// 마우스 커서 좌표를 화면에 뿌려줄 값
	//D3DXMatrixTranslation(&m_matTrans2, 600.f, 80.f, 0.f);

	//wsprintf(m_szMouse, L"X: %d, Y: %d", (int)GetMouse().x, (int)GetMouse().y);

}

void CMainGame::Render()
{
	++m_iCount;

	m_fTime += GET_TIME;

	if (1.f < m_fTime)
	{
		m_fTime = 0.f;
		wsprintf(m_szFPS, L"FPS : %d", m_iCount);
		m_iCount = 0;
	}

	m_pDevice->Render_Begin();

	m_pScene->Render(m_hDC);

	m_pDevice->GetSprite()->SetTransform(&m_matTrans);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(),
		m_szFPS,
		lstrlen(m_szFPS),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 0, 0, 0));

	//m_pDevice->GetSprite()->SetTransform(&m_matTrans2);

	//m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(),
	//	m_szMouse,
	//	lstrlen(m_szMouse),
	//	NULL,
	//	NULL,
	//	D3DCOLOR_ARGB(255, 0, 0, 0));

	m_pDevice->Render_End();
}

void CMainGame::Release()
{
	CSoundMgr::GetInstance()->DestroyInstance();
	CAStar::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CScrollMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();

	m_pScene->DestroyInstance();
	m_pDevice->DestroyInstance();

	ReleaseDC(g_hWnd, m_hDC);
}
