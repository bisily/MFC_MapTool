#include "stdafx.h"
#include "EffectDead.h"


CEffectDead::CEffectDead()
{
}

CEffectDead::CEffectDead(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectDead::~CEffectDead()
{
}

HRESULT CEffectDead::Initialize()
{
	return S_OK;
}

int CEffectDead::Progress(INFO & rInfo)
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

void CEffectDead::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectDead::Release()
{
}
