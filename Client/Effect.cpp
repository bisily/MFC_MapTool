#include "stdafx.h"
#include "Effect.h"
#include "Bridge.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

HRESULT CEffect::Initialize()
{
	m_wstrObjKey = L"EFFECT";
	
	m_eLayer = RENDER_EFFECT;

	return S_OK;
}

int CEffect::Progress()
{
	int iResult = 0;

	if (nullptr != m_pBridge)
	{
		iResult = m_pBridge->Progress(m_tInfo);

		m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
		m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
		m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
		m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);
	}


	if (1 == iResult)
	{
		delete this;
		return 1;
	}

	return iResult;
}

void CEffect::Render(HDC hDC)
{
	if (nullptr != m_pBridge)
		m_pBridge->Render(hDC);
}

void CEffect::Release()
{
	if (nullptr != m_pBridge)
		::Safe_Delete(m_pBridge);
}
