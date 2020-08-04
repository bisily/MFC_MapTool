#include "stdafx.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "BridgeFactory.h"
#include "Effect.h"
#include "EffectClick.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

HRESULT CMouse::Initialize(void)
{
	m_wstrObjKey = L"CURSOR";
	m_wstrStateKey = L"Cursor";

	m_tFrame = FRAME(0.f, 0.f, 0.f);

	m_eLayer = RENDER_UI;

	return S_OK;
}

int CMouse::Progress(void)
{
	m_tInfo.vPos.x = GetMouse().x;
	m_tInfo.vPos.y = GetMouse().y;


	if (!lstrcmp(m_wstrStateKey.c_str(), L"Hand") ||
		!lstrcmp(m_wstrStateKey.c_str(), L"Take"))
	{
		FrameMove();
	}

	if (lstrcmp(m_wstrStateKey.c_str(), L"Hand") &&
		lstrcmp(m_wstrStateKey.c_str(), L"Take"))
	{
		m_tFrame = FRAME(0.f, 0.f, 0.f);
	}

	WorldMatrix();

	return 0;
}

void CMouse::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CMouse::Release(void)
{
}

void CMouse::FrameMove()
{
	if (m_wstrObjKey == L"HAND" && m_bCheckFrame)
	{
		m_bCheckFrame = !m_bCheckFrame;
		m_tFrame = FRAME(0.f, 2.f, 2.f);
	}
	if (m_wstrObjKey == L"TAKE" && m_bCheckTake)
	{
		m_bCheckTake = !m_bCheckTake;
		m_tFrame = FRAME(0.f, 2.f, 2.f);
	}

	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = 0.f;
	}
}

void CMouse::WorldMatrix()
{
	D3DXMATRIX			matTrans;

	D3DXMatrixTranslation(&matTrans,
							m_tInfo.vPos.x,
							m_tInfo.vPos.y,
							0.f);

	m_tInfo.matWorld = matTrans;

}
