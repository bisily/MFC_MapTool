#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_MainView = ((CMainFrame*)AfxGetMainWnd())->GetToolView();

	m_tFrame = FRAME(0.f, 0.f, 0.f);
	m_fSpeed = 10.f;


	D3DXMatrixIdentity(&m_tInfo.matWorld);

	return S_OK;
}

int CPlayer::Progress(void)
{
	return 0;
}

void CPlayer::Render(void)
{
	const TEXINFO*		pTexture = CToolTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, 0);

	if (nullptr == pTexture)
		return;

	D3DXMATRIX			matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - m_MainView->GetScrollPos(0),
		m_tInfo.vPos.y - m_MainView->GetScrollPos(1),
		0.f);

	m_tInfo.matWorld = matTrans;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release(void)
{
}
