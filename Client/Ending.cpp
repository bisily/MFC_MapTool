#include "stdafx.h"
#include "Ending.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

HRESULT CEnding::Initialize()
{
	CSoundMgr::GetInstance()->StopSoundAll();

	CSoundMgr::GetInstance()->PlayBGM(L"feliz3.wav");

	return S_OK;
}

int CEnding::Progress()
{

	return 0;
}

void CEnding::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"ENDING");

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	D3DXMATRIX		matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	// 로고 이미지 출력
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEnding::Release()
{
}
