#include "stdafx.h"
#include "SniperRifle.h"


CSniperRifle::CSniperRifle()
{
}


CSniperRifle::~CSniperRifle()
{
	Release();
}

HRESULT CSniperRifle::Initialize()
{
	m_tInfo.vPos = { 480.f, 1050.f, 0.f };

	fCX = 50.f;
	fCY = 25.f;

	m_iHp = 1;

	m_wstrObjKey = L"SNIPERRIFLE";
	m_wstrStateKey = L"SniperRifle";
	m_wstrCount = L"0";

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CSniperRifle::Progress()
{
	if (0 >= m_iHp)
	{
		return 1;
	}

	DrawRect();

	return 0;
}

void CSniperRifle::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, _ttoi(m_wstrCount.c_str()));

	if (nullptr == pTexture)
		return;

	D3DXMATRIX			matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
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

void CSniperRifle::Release()
{
}

void CSniperRifle::DrawRect()
{
	float centerX = m_tInfo.vPos.x + (fCX / 2.f);
	float centerY = m_tInfo.vPos.y + (fCY / 2.f);

	m_tRect.left = LONG(centerX - (fCX));
	m_tRect.top = LONG(centerY - (fCY * 1.4f));
	m_tRect.right = LONG(m_tRect.left + (fCX));
	m_tRect.bottom = LONG(m_tRect.top + (fCY));
}