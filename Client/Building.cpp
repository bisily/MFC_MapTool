#include "stdafx.h"
#include "Building.h"


CBuilding::CBuilding()
{
}


CBuilding::~CBuilding()
{
	Release();
}

HRESULT CBuilding::Initialize(void)
{
	CString szBuffer = m_wstrObjKey.c_str();
	
	int retval = 0;
	retval = szBuffer.Find('_');
	m_wstrObjKey = szBuffer.Left(retval);

	transform(m_wstrObjKey.begin(), m_wstrObjKey.end(), m_wstrObjKey.begin(), towupper);
	m_wstrStateKey = szBuffer.Left(retval);
	m_wstrCount = szBuffer.Mid(retval + 1);

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CBuilding::Progress(void)
{
	DrawRect();

	return 0;
}

void CBuilding::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, _ttoi(m_wstrCount.c_str()));

	if (nullptr == pTexture)
		return;

	D3DXMATRIX			matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	fCX = fX;
	fCY = fY;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBuilding::Release(void)
{
}

void CBuilding::DrawRect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x - fCX);
	m_tRect.top = LONG(m_tInfo.vPos.y - fCY);
	m_tRect.right = LONG(m_tInfo.vPos.x + fCX);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY);
}
