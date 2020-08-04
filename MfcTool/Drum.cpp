#include "stdafx.h"
#include "Drum.h"


CDrum::CDrum()
{
}


CDrum::~CDrum()
{
}

HRESULT CDrum::Initialize()
{
	m_MainView = ((CMainFrame*)AfxGetMainWnd())->GetToolView();

	CString szBuffer = m_wstrObjKey.c_str();


	int retval = 0;
	retval = szBuffer.Find('_');
	m_wstrObjKey = szBuffer.Left(retval);

	transform(m_wstrObjKey.begin(), m_wstrObjKey.end(), m_wstrObjKey.begin(), towupper);
	m_wstrStateKey = szBuffer.Left(retval);
	m_wstrCount = szBuffer.Mid(retval + 1);

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	return S_OK;
}

int CDrum::Progress()
{
	
	return 0;
}

void CDrum::Render()
{
	const TEXINFO*		pTexture = CToolTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, _ttoi(m_wstrCount.c_str()));

	if (nullptr == pTexture)
		return;

	D3DXMATRIX			matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - m_MainView->GetScrollPos(0),
		m_tInfo.vPos.y - m_MainView->GetScrollPos(1),
		0.f);

	m_tInfo.matWorld = matTrans;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDrum::Release()
{
}
