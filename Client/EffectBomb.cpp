#include "stdafx.h"
#include "EffectBomb.h"


CEffectBomb::CEffectBomb()
{
}

CEffectBomb::CEffectBomb(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectBomb::~CEffectBomb()
{
	Release();
}

HRESULT CEffectBomb::Initialize()
{
	return S_OK;
}

int CEffectBomb::Progress(INFO & rInfo)
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

void CEffectBomb::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectBomb::Release()
{
}
