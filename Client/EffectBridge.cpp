#include "stdafx.h"
#include "EffectBridge.h"


CEffectBridge::CEffectBridge()
{
}

CEffectBridge::CEffectBridge(CObj * pObj)
	: CBridge(pObj)
{
}


CEffectBridge::~CEffectBridge()
{
}

void CEffectBridge::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_pObj->GetObjKey(), m_wstrStateKey, (int)m_tFrame.fFrame);

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}
