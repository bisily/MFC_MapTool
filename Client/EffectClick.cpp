#include "stdafx.h"
#include "EffectClick.h"


CEffectClick::CEffectClick()
{
}

CEffectClick::CEffectClick(CObj * pObj)
	: CEffectBridge(pObj)
{
}


CEffectClick::~CEffectClick()
{
	Release();
}

HRESULT CEffectClick::Initialize()
{

	return S_OK;
}

int CEffectClick::Progress(INFO & rInfo)
{
	D3DXMATRIX			matTrans;

	D3DXMatrixTranslation(&matTrans,
		rInfo.vPos.x,
		rInfo.vPos.y,
		0.f);

	rInfo.matWorld = matTrans;

	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		return 1;

	return 0;
}

void CEffectClick::Render(HDC hDC)
{
	CEffectBridge::Render(hDC);
}

void CEffectClick::Release()
{
}
