#include "stdafx.h"
#include "EffectFire.h"


CEffectFire::CEffectFire()
{
}

CEffectFire::CEffectFire(CObj * pObj)
	: CEffectBridge(pObj)
{
}

CEffectFire::~CEffectFire()
{
	Release();
}

HRESULT CEffectFire::Initialize()
{
	return S_OK;
}

int CEffectFire::Progress(INFO & rInfo)
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

void CEffectFire::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectFire::Release()
{
}
