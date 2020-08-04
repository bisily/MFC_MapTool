#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
}


CUI::~CUI()
{
	Release();
}

HRESULT CUI::Initialize(void)
{
	m_wstrObjKey = L"VIEW";
	m_wstrStateKey = L"View";

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	
	m_eLayer = RENDER_UI;
	
	return S_OK;
}

int CUI::Progress(void)
{
	return 0;
}

void CUI::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, 0);

	if (nullptr == pTexture)
		return;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI::Release(void)
{
}
