#include "stdafx.h"
#include "EffectExplosion.h"


CEffectExplosion::CEffectExplosion()
{
}

CEffectExplosion::CEffectExplosion(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectExplosion::~CEffectExplosion()
{
	Release();
}

HRESULT CEffectExplosion::Initialize()
{
	return S_OK;
}

int CEffectExplosion::Progress(INFO & rInfo)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans
		, rInfo.vPos.x + m_pObj->GetScroll().x
		, rInfo.vPos.y + m_pObj->GetScroll().y
		, 0.f);

	rInfo.matWorld = matTrans;

	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		return 1;
	}


	return 0;
}

void CEffectExplosion::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectExplosion::Release()
{
}
