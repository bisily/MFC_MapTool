#include "stdafx.h"
#include "Boat.h"
#include "Player.h"

CBoat::CBoat()
{
}


CBoat::~CBoat()
{
	Release();
}

HRESULT CBoat::Initialize()
{
	m_tInfo.vPos = { 285.f, 975.f, 0.f };

	m_wstrObjKey = L"BOAT";
	m_wstrStateKey = L"BoatB";
	m_wstrCount = L"0";

	m_fSpeed = 80.f;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	m_eLayer = RENDER_BOAT;

	return S_OK;
}

int CBoat::Progress()
{
	DrawRect();
	
	KeyCheck();
	return 0;
}

void CBoat::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, _ttoi(m_wstrCount.c_str()));

	if (nullptr == pTexture)
		return;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	fCX = fX * 2;
	fCY = fY * 2;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBoat::Release()
{
}

void CBoat::DrawRect()
{
	float centerX = m_tInfo.vPos.x + (fCX / 2.f);
	float centerY = m_tInfo.vPos.y + (fCY / 2.f);

	m_tRect.left = LONG(centerX - (fCX));
	m_tRect.top = LONG(centerY - (fCY * 1.4f));
	m_tRect.right = LONG(m_tRect.left + (fCX));
	m_tRect.bottom = LONG(m_tRect.top + (fCY));
}

void CBoat::KeyCheck()
{
	if (nullptr != m_pTarget)
	{
		// 왼쪽
		if (KEY_PRESSING(VK_LEFT))
		{
			// 왼쪽 위 이동
			if (KEY_PRESSING(VK_UP))
			{
				m_tInfo.vPos.x -= (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y -= (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_wstrStateKey = L"BoatLU";
			}
			// 왼쪽 아래 이동
			else if (KEY_PRESSING(VK_DOWN))
			{
				m_tInfo.vPos.x -= (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_wstrStateKey = L"BoatLB";
			}
			// 왼쪽 이동
			else
			{
				m_tInfo.vPos.x -= m_fSpeed * GET_TIME;
				m_wstrStateKey = L"BoatL";
			}

		}
		// 오른쪽
		else if (KEY_PRESSING(VK_RIGHT))
		{
			// 오른쪽 위 이동
			if (KEY_PRESSING(VK_UP))
			{
				m_tInfo.vPos.x += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y -= (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_wstrStateKey = L"BoatRU";
			}
			// 오른쪽 아래 이동
			else if (KEY_PRESSING(VK_DOWN))
			{
				m_tInfo.vPos.x += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_wstrStateKey = L"BoatRB";
			}
			// 오른쪽 이동
			else
			{
				m_tInfo.vPos.x += m_fSpeed * GET_TIME;
				m_wstrStateKey = L"BoatR";
			}

		}
		// 위 이동
		else if (KEY_PRESSING(VK_UP))
		{
			m_tInfo.vPos.y -= m_fSpeed * GET_TIME;
			m_wstrStateKey = L"BoatU";
		}
		// 아래 이동
		else if (KEY_PRESSING(VK_DOWN))
		{
			m_tInfo.vPos.y += m_fSpeed * GET_TIME;
			m_wstrStateKey = L"BoatB";
		}

		if (KEY_DOWN('V'))
		{
			D3DXVECTOR3 vTemPos(m_tInfo.vPos.x + fCX, m_tInfo.vPos.y + (fCY / 2), 0.f);
			m_pTarget->SetPos(vTemPos);
			dynamic_cast<CPlayer*>(m_pTarget)->SetStand();
			m_pTarget->SetStateKey(L"IdleR");

			m_pTarget = nullptr;
		}
	}
}
