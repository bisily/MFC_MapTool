#include "stdafx.h"
#include "EffectSplash.h"


CEffectSplash::CEffectSplash()
{
}

CEffectSplash::CEffectSplash(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectSplash::~CEffectSplash()
{
}

HRESULT CEffectSplash::Initialize()
{
	return S_OK;
}

int CEffectSplash::Progress(INFO & rInfo)
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

void CEffectSplash::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectSplash::Release()
{
}
