#include "stdafx.h"
#include "Car.h"
#include "SceneMgr.h"


CCar::CCar()
{
}

CCar::~CCar()
{
	Release();
}

HRESULT CCar::Initialize()
{
	m_tInfo.vPos = { 200.f, 2200.f, 0.f };
	
	m_wstrObjKey = L"CAR";
	m_wstrStateKey = L"CarB";
	m_wstrCount = L"0";

	m_fSpeed = 150.f;
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CCar::Progress()
{
	
	if (nullptr != m_pTarget)
	{
		m_iTime += GET_TIME;

		if (m_iTime > 2)
		{
			m_iTime = 0;

			CSoundMgr::GetInstance()->PlayerSound(L"Drive.wav", CSoundMgr::CHANNEL_DRIVE);
		}
	}

	if (m_tRect.left >= 1400)
	{
		CSceneMgr::GetInstance()->SetScene(SC_ENDING);

		return 0;
	}


	DrawRect();

	KeyCheck();

	return 0;
}

void CCar::Render(HDC hDC)
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

void CCar::Release()
{
}

void CCar::DrawRect()
{
	float centerX = m_tInfo.vPos.x + (fCX / 2.f);
	float centerY = m_tInfo.vPos.y + (fCY / 2.f);

	m_tRect.left	= LONG(centerX - (fCX));
	m_tRect.top		= LONG(centerY - (fCY * 1.4f));
	m_tRect.right	= LONG(m_tRect.left + (fCX));
	m_tRect.bottom	= LONG(m_tRect.top + (fCY));
}

void CCar::KeyCheck()
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
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarRU";
			}

			// 왼쪽 아래 이동
			else if (KEY_PRESSING(VK_DOWN))
			{
				m_tInfo.vPos.x -= (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarRB";
			}

			// 왼쪽 이동
			else
			{
				m_tInfo.vPos.x -= m_fSpeed * GET_TIME;
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarR";
			}

			if (!m_bDriveStart)
			{
				m_bDriveStart = true;
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
				D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarRU";
			}

			// 오른쪽 아래 이동
			else if (KEY_PRESSING(VK_DOWN))
			{
				m_tInfo.vPos.x += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				m_tInfo.vPos.y += (m_fSpeed / sqrtf(2.f)) * GET_TIME;
				D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarRB";
			}

			// 오른쪽 이동
			else
			{
				m_tInfo.vPos.x += m_fSpeed * GET_TIME;
				D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
				m_wstrStateKey = L"CarR";
			}

			if (!m_bDriveStart)
			{
				m_bDriveStart = true;
			}

		}

		// 위 이동
		else if (KEY_PRESSING(VK_UP))
		{
			m_tInfo.vPos.y -= m_fSpeed * GET_TIME;
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			m_wstrStateKey = L"CarU";

			if (!m_bDriveStart)
			{
				m_bDriveStart = true;
			}

		}

		// 아래 이동
		else if (KEY_PRESSING(VK_DOWN))
		{
			m_tInfo.vPos.y += m_fSpeed * GET_TIME;
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			m_wstrStateKey = L"CarB";

			if (!m_bDriveStart)
			{
				m_bDriveStart = true;
			}

		}
	}
}
