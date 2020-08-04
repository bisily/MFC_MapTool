#include "stdafx.h"
#include "EffectShoot.h"


CEffectShoot::CEffectShoot()
{
}

CEffectShoot::CEffectShoot(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectShoot::~CEffectShoot()
{
	Release();
}

HRESULT CEffectShoot::Initialize()
{
	return S_OK;
}

int CEffectShoot::Progress(INFO & rInfo)
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

void CEffectShoot::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectShoot::Release()
{
}
