#include "stdafx.h"
#include "Generator.h"
#include "Effect.h"
#include "BridgeFactory.h"
#include "EffectExplosion.h"
#include "EffectBigExplosion.h"

CGenerator::CGenerator()
{
}


CGenerator::~CGenerator()
{
}

HRESULT CGenerator::Initialize()
{
	CString szBuffer = m_wstrObjKey.c_str();

	int retval = 0;
	retval = szBuffer.Find('_');
	m_wstrObjKey = szBuffer.Left(retval);

	transform(m_wstrObjKey.begin(), m_wstrObjKey.end(), m_wstrObjKey.begin(), towupper);
	m_wstrStateKey = szBuffer.Left(retval);
	m_wstrCount = szBuffer.Mid(retval + 1);

	m_tFrame = FRAME(0.f, 0.f, 0.f);

	fCX = 160.f;
	fCY = 230.f;

	m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
	m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
	m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);

	m_fSpeed = 0.f;

	m_iHp = 1;

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CGenerator::Progress()
{
	if (0 >= m_iHp)
	{
		m_dExplosionTime += GET_TIME;

		if (5 > m_iCreateCnt && m_dExplosionTime > 0.5)
		{
			m_dExplosionTime = 0;
			m_iCreateCnt++;

			srand((unsigned int)time(NULL));

			float fPosX = float(rand() % 40);
			float fPosY = float(rand() % 40);

			if (m_iCreateCnt % 2 == 0)
			{
				fPosX = m_tInfo.vPos.x + fPosX;
				fPosY = m_tInfo.vPos.y + fPosY;
			}
			else
			{
				fPosX = m_tInfo.vPos.x - fPosX;
				fPosY = m_tInfo.vPos.y - fPosY;
			}

			CObj* pEffect = CBridgeFactory<CEffectExplosion>::CreateEffect(L"Explosion", D3DXVECTOR3(fPosX, fPosY, 0.f), 50, 60);
			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

			CSoundMgr::GetInstance()->PlayerSound(L"Explosion.wav", CSoundMgr::CHANNEL_BOMB);
		}

		if (5 == m_iCreateCnt)
		{
			CObjMgr::GetInstance()->SetClearContion();
			
			if (m_dExplosionTime > 1)
			{
				m_dExplosionTime = 0.f;
				m_iCreateCnt++;
				CObj* pEffect = CBridgeFactory<CEffectBigExplosion>::CreateEffect(L"BigExplosion", m_tInfo.vPos, 100, 100);
				CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

				CSoundMgr::GetInstance()->PlayerSound(L"Bomb.wav", CSoundMgr::CHANNEL_BOMB);
				m_wstrCount = L"1";
			}
		}
	}

	return 0;
}

void CGenerator::Render(HDC hDC)
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

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGenerator::Release()
{
}
