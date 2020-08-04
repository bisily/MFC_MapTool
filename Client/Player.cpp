#include "stdafx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "BridgeFactory.h"
#include "EffectShoot.h"
#include "EffectBomb.h"
#include "MathMgr.h"
#include "Boat.h"
#include "Mouse.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{
	m_tFrame = FRAME(0.f, 0.f, 0.f);
	
	fCX = 24.f;
	fCY = 42.f;
	
	m_tRect.left	= LONG(m_tInfo.vPos.x - fCX / 2);
	m_tRect.top		= LONG(m_tInfo.vPos.y - fCY / 2);
	m_tRect.right	= LONG(m_tInfo.vPos.x + fCX / 2);
	m_tRect.bottom	= LONG(m_tInfo.vPos.y + fCY / 2);

	m_fSpeed = 100.f;

	m_iHp = 100;
	m_wstrStateKey = L"IdleB";
	m_wstrCount = L"0";

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CPlayer::Progress()
{
	DrawRect();

	CheckKey();
	AStarMove();

	FrameMove();
	WorldMatrix();

	return 0;
}

void CPlayer::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
	CMathMgr::GetInstance()->DestroyInstance();
}

void CPlayer::FrameMove()
{	
	// 대기 상태
	if (CAStar::GetInstance()->GetBestList()->empty()		&& 
		!m_bPressingButton									&&
		!m_bSit												&&
		lstrcmp(m_pMouse->GetObjKey().c_str(), L"SNIPING"))
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		if (nullptr == m_pDrum)
		{
			if ((0 <= m_fAngle && 15 >= m_fAngle) ||
				(345 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"IdleR";
			}

			else if (16 <= m_fAngle && 65 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleRU";
			}

			else if (66 <= m_fAngle && 110 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleU";
			}

			else if (111 <= m_fAngle && 156 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleLU";
			}

			else if (157 <= m_fAngle && 202 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleL";
			}

			else if (203 <= m_fAngle && 248 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleLB";
			}

			else if (249 <= m_fAngle && 294 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleB";
			}

			else if (295 <= m_fAngle && 340 >= m_fAngle)
			{
				m_wstrStateKey = L"IdleRB";
			}
		}
		else if (nullptr != m_pDrum)
		{
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			
			if ((0 <= m_fAngle && 15 >= m_fAngle) ||
				(345 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"DWorkR";
			}

			else if (16 <= m_fAngle && 65 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkRU";
			}

			else if (66 <= m_fAngle && 110 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkU";
			}

			else if (111 <= m_fAngle && 156 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkRU";
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
			}

			else if (157 <= m_fAngle && 202 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkR";
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
			}

			else if (203 <= m_fAngle && 248 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkRB";
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
			}

			else if (249 <= m_fAngle && 294 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkB";
			}

			else if (295 <= m_fAngle && 340 >= m_fAngle)
			{
				m_wstrStateKey = L"DWorkRB";
			}
		}

		m_tFrame = FRAME(0.f, 0.f, 0.f);
	}

	// 걷기
	else if (!lstrcmp(m_pMouse->GetObjKey().c_str(), L"CURSOR") &&
		nullptr == m_pDrum										&&
		!m_bSit)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

		m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

		if ((0 <= m_fAngle && 22.5 >= m_fAngle) ||
			(337.6 <= m_fAngle && 360 >= m_fAngle))
		{
			m_wstrStateKey = L"WorkR";
		}

		else if (22.6 <= m_fAngle && 67.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkRU";
		}

		else if (67.5 <= m_fAngle && 112 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkU";
		}

		else if (112.5 <= m_fAngle && 157.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkLU";
		}

		else if (157.6 <= m_fAngle && 202.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkL";
		}

		else if (202.6 <= m_fAngle && 247.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkLB";
		}

		else if (247.6 <= m_fAngle && 292.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkB";
		}

		else if (292.6 <= m_fAngle && 337.5 >= m_fAngle)
		{
			m_wstrStateKey = L"WorkRB";
		}

		if (m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_tFrame.fFrame = 0.f;
		}

		if (m_bWalkSound)
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_PLAYER);

			m_bWalkSound = FALSE;

			srand((unsigned int)time(NULL));

			int iNum = rand() % 10;
			CString temp;

			switch (iNum)
			{
			case 0:
				temp = L"Player_0.wav";
				break;

			case 1:
				temp = L"Player_1.wav";
				break;

			case 2:
				temp = L"Player_2.wav";
				break;

			case 3:
				temp = L"Player_3.wav";
				break;

			case 4:
				temp = L"Player_4.wav";
				break;

			case 5:
				temp = L"Player_5.wav";
				break;

			case 6:
				temp = L"Player_6.wav";
				break;

			case 7:
				temp = L"Player_7.wav";
				break;

			case 8:
				temp = L"Player_8.wav";
				break;

			case 9:
				temp = L"Player_9.wav";
				break;
			}

			CSoundMgr::GetInstance()->PlayerSound(temp, CSoundMgr::CHANNEL_PLAYER);
		}

	}
	
	// 칼
	else if (!lstrcmp(m_pMouse->GetObjKey().c_str(), L"KNIFE"))
	{
		if (m_bKnifeAttack)
		{
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

			if (m_tFrame.fFrame < m_tFrame.fMax)
			{
				m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;
			}

			if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_tFrame.fFrame = 0.f;

				if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeR"))
				{
					m_wstrStateKey = L"IdleR";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeRU"))
				{
					m_wstrStateKey = L"IdleRU";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeU"))
				{
					m_wstrStateKey = L"IdleU";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeLU"))
				{
					m_wstrStateKey = L"IdleLU";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeL"))
				{
					m_wstrStateKey = L"IdleL";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeB"))
				{
					m_wstrStateKey = L"IdleLB";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeB"))
				{
					m_wstrStateKey = L"IdleB";
				}

				else if (!lstrcmp(m_wstrStateKey.c_str(), L"KnifeRB"))
				{
					m_wstrStateKey = L"IdleRB";
				}

				m_tFrame = FRAME(0.f, 0.f, 0.f);

				m_bKnifeAttack = false;

			}
		}
	}

	// 총
	else if (!lstrcmp(m_pMouse->GetObjKey().c_str(), L"GUN"))
	{
		if (m_tFrame.fFrame < m_tFrame.fMax)
		{
			m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;
		}
		
		if (KEY_PRESSING(VK_LBUTTON))
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_EFFECT);

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

			m_vDir = (GetMouse() - m_vScroll) - m_tInfo.vPos;

			D3DXVec3Normalize(&m_vDir, &m_vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

			float fCos = D3DXVec3Dot(&m_vDir, &m_tInfo.vLook);

			float fAngle = acosf(fCos);

			if (m_tInfo.vPos.y < GetMouse().y - m_vScroll.y)
			{
				fAngle = 2 * D3DX_PI - fAngle;
			}

			float fAngle_Degree = D3DXToDegree(fAngle);

			if ((0 <= fAngle_Degree && 18 >= fAngle_Degree) ||
				(340 <= fAngle_Degree && 360 >= fAngle_Degree))
			{
				m_wstrStateKey = L"ShootR";
			}

			else if (19 <= fAngle_Degree && 64 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootRU";
			}

			else if (65 <= fAngle_Degree && 109 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootU";
			}

			else if (110 <= fAngle_Degree && 155 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootLU";
			}

			else if (156 <= fAngle_Degree && 201 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootL";
			}

			else if (202 <= fAngle_Degree && 247 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootLB";
			}

			else if (248 <= fAngle_Degree && 293 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootB";
			}

			else if (294 <= fAngle_Degree && 339 >= fAngle_Degree)
			{
				m_wstrStateKey = L"ShootRB";
			}

			m_tFrame.fFrame = 3.f;
			
			if (CMathMgr::GetInstance()->CalcDistance(::GetMouse(), m_tInfo.vPos + m_vScroll) < 300)
			{
				CObj* pEffect = CBridgeFactory<CEffectShoot>::CreateEffect(L"Shoot", ::GetMouse() - m_vScroll);

				CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

				if (!m_bFireSound)
				{
					m_bFireSound = !m_bFireSound;
					CSoundMgr::GetInstance()->PlayerSound(L"Fire.wav", CSoundMgr::CHANNEL_EFFECT);
				}
			}

		}

		if(m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_tFrame.fFrame = m_tFrame.fMax;
		}

		m_bFireSound = !m_bFireSound;
	}

	// 스나이퍼
	else if (!lstrcmp(m_pMouse->GetObjKey().c_str(), L"SNIPING"))
	{

		if (KEY_PRESSING(VK_LBUTTON))
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_EFFECT);

			if (CMathMgr::GetInstance()->CalcDistance(::GetMouse(), m_tInfo.vPos + m_vScroll) < 700)
			{
				CObj* pEffect = CBridgeFactory<CEffectShoot>::CreateEffect(L"Shoot", ::GetMouse() - m_vScroll);

				CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

				CSoundMgr::GetInstance()->PlayerSound(L"Sniping.wav", CSoundMgr::CHANNEL_EFFECT);

			}
		}

		m_tFrame = FRAME{ 0.f, 0.f, 0.f };
	}

	// 드럼통을 들고 걷기
	else if (nullptr != m_pDrum)
	{
		m_fSpeed = 80.f;

		m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

		if ((0 <= m_fAngle && 15 >= m_fAngle) ||
			(345 <= m_fAngle && 360 >= m_fAngle))
		{
			m_wstrStateKey = L"DWorkR";
		}

		else if (16 <= m_fAngle && 65 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkRU";
		}

		else if (66 <= m_fAngle && 110 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkU";
		}

		else if (111 <= m_fAngle && 156 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkRU";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (157 <= m_fAngle && 202 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkR";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (203 <= m_fAngle && 248 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkRB";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (249 <= m_fAngle && 294 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkB";
		}

		else if (295 <= m_fAngle && 340 >= m_fAngle)
		{
			m_wstrStateKey = L"DWorkRB";
		}

		if (m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_tFrame.fFrame = 0.f;
		}

		if (m_bWalkSound)
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_PLAYER);
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_DRUMMOVE);

			m_bWalkSound = FALSE;

			srand((unsigned int)time(NULL));

			int iNum = rand() % 10;
			CString temp;

			switch (iNum)
			{
			case 0:
				temp = L"Player_0.wav";
				break;

			case 1:
				temp = L"Player_1.wav";
				break;

			case 2:
				temp = L"Player_2.wav";
				break;

			case 3:
				temp = L"Player_3.wav";
				break;

			case 4:
				temp = L"Player_4.wav";
				break;

			case 5:
				temp = L"Player_5.wav";
				break;

			case 6:
				temp = L"Player_6.wav";
				break;

			case 7:
				temp = L"Player_7.wav";
				break;

			case 8:
				temp = L"Player_8.wav";
				break;

			case 9:
				temp = L"Player_9.wav";
				break;
			}

			CSoundMgr::GetInstance()->PlayerSound(temp, CSoundMgr::CHANNEL_PLAYER);
			CSoundMgr::GetInstance()->PlayerSound(L"DrumMove.wav", CSoundMgr::CHANNEL_DRUMMOVE);
		}
	}
	
	else if (m_bSit)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

		m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

		CObj* pObj = CObjMgr::GetInstance()->FindObj(OBJ_ACTIVE, L"BOAT");

		m_tInfo.vPos = pObj->GetInfo()->vPos;

		if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatR"))
		{
			m_wstrStateKey = L"SitR";
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatRU"))
		{
			m_wstrStateKey = L"SitRU";
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatU"))
		{
			m_wstrStateKey = L"SitU";
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatLU"))
		{
			m_wstrStateKey = L"SitRU";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatL"))
		{
			m_wstrStateKey = L"SitR";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatLB"))
		{
			m_wstrStateKey = L"SitRB";
			D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatB"))
		{
			m_wstrStateKey = L"SitB";
		}

		else if (!lstrcmp(pObj->GetStateKey().c_str(), L"BoatRB"))
		{
			m_wstrStateKey = L"SitRB";
		}
		
		m_tFrame = FRAME(0.f, 0.f, 0.f);
	}
}

void CPlayer::CheckKey()
{
	// 칼
	if (KEY_DOWN('Z'))
	{
		m_bPressingButton = !m_bPressingButton;

		m_pMouse->SetObjKey(L"KNIFE");
		m_pMouse->SetStateKey(L"");

		if (m_bKnifeAttack)
		{
			m_vDir = (GetMouse() - m_vScroll) - m_tInfo.vPos;

			D3DXVec3Normalize(&m_vDir, &m_vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

			float fCos = D3DXVec3Dot(&m_vDir, &m_tInfo.vLook);

			float fAngle = acosf(fCos);
		
			if (m_tInfo.vPos.y < GetMouse().y - m_vScroll.y)
			{
				fAngle = 2 * D3DX_PI - fAngle;
			}

			float fAngle_Degree = D3DXToDegree(fAngle);
	
			if ((0 <= fAngle_Degree && 18 >= fAngle_Degree) ||
				(340 <= fAngle_Degree && 360 >= fAngle_Degree))
			{
				m_wstrStateKey = L"KnifeR";
			}

			else if (19 <= fAngle_Degree && 64 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeRU";
			}

			else if (65 <= fAngle_Degree && 109 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeU";
			}

			else if (110 <= fAngle_Degree && 155 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeLU";
			}

			else if (156 <= fAngle_Degree && 201 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeL";
			}

			else if (202 <= fAngle_Degree && 247 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeLB";
			}

			else if (248 <= fAngle_Degree && 293 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeB";
			}

			else if (294 <= fAngle_Degree && 339 >= fAngle_Degree)
			{
				m_wstrStateKey = L"KnifeRB";
			}

			//m_tFrame = FRAME(0.f, 4.f, 4.f);
		}
	}

	// 총
	if (KEY_DOWN('X'))
	{
		// 움직일 거리가 없을 경우
		if (CAStar::GetInstance()->GetBestList()->empty())
		{
			m_bPressingButton = TRUE;
		
			m_fSpeed = 0.f;

			m_pMouse->SetObjKey(L"GUN");
			m_pMouse->SetStateKey(L"");

			m_vDir = (GetMouse() - m_vScroll) - m_tInfo.vPos;

			D3DXVec3Normalize(&m_vDir, &m_vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

			float fCos = D3DXVec3Dot(&m_vDir, &m_tInfo.vLook);

			m_fAngle = acosf(fCos);

			if (m_tInfo.vPos.y < GetMouse().y - m_vScroll.y)
			{
				m_fAngle = 2 * D3DX_PI - m_fAngle;
			}

			m_fAngle = D3DXToDegree(m_fAngle);

			if ((0 <= m_fAngle && 18 >= m_fAngle) ||
				(340 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"ShootR";
			}

			else if (19 <= m_fAngle && 64 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootRU";
			}

			else if (65 <= m_fAngle && 109 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootU";
			}

			else if (110 <= m_fAngle && 155 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootLU";
			}

			else if (156 <= m_fAngle && 201 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootL";
			}

			else if (202 <= m_fAngle && 247 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootLB";
			}

			else if (248 <= m_fAngle && 293 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootB";
			}

			else if (294 <= m_fAngle && 339 >= m_fAngle)
			{
				m_wstrStateKey = L"ShootRB";
			}
		
			m_tFrame = FRAME(0.f, 4.f, 4.f);

			m_fSpeed = 0.f;
		}
	}
	
	// 마우스 왼쪽을 누르고 
	// 커서가 총모양이 아니고 
	// m_pDrum이 nullptr 일때 움직여라
	if (KEY_DOWN(VK_LBUTTON) && 
		lstrcmp(m_pMouse->GetObjKey().c_str(), L"GUN")		&&
		lstrcmp(m_pMouse->GetObjKey().c_str(), L"SNIPING"))
	{
		D3DXVECTOR3		vMousePos = ::GetMouse() - m_vScroll;
		CAStar::GetInstance()->AStarStartPos(m_tInfo.vPos, vMousePos);

		if (!CAStar::GetInstance()->GetBestList()->empty())
		{
			m_bWalkSound = !m_bWalkSound;
			m_tFrame = FRAME(0.f, 7.f, 7.f);
		}
	}

	// 마우스 오른쪽 버튼을 누르고 마우스 커서가 '커서'가 아닐 경우
	if (KEY_DOWN(VK_RBUTTON) && lstrcmp(m_pMouse->GetObjKey().c_str(), L"CURSOR"))
	{
		m_bPressingButton = FALSE;

		m_pMouse->SetObjKey(L"CURSOR");
		m_pMouse->SetStateKey(L"Cursor");

		// 이동할 거리가 없거나 드럼포인터가 nullptr이 아닐 때
		if (CAStar::GetInstance()->GetBestList()->empty() &&
			nullptr != m_pDrum)
		{
			m_pDrum->SetPos((m_tInfo.vPos.x + fCX / 2), m_tInfo.vPos.y);

			m_pDrum = nullptr;
		}
		
		m_fSpeed = 100.f;

		m_tFrame = FRAME(0.f, 0.f, 0.f);
	}

	// 손 모양
	if (KEY_DOWN('H'))
	{
		m_pMouse->SetObjKey(L"HAND");
		m_pMouse->SetStateKey(L"Hand");
		dynamic_cast<CMouse*>(m_pMouse)->SetAbleFrameSetHand(true);
	}

	// 레버 당기는 모양
	if(KEY_DOWN('C'))
	{
		m_pMouse->SetObjKey(L"TAKE");
		m_pMouse->SetStateKey(L"Take");
		dynamic_cast<CMouse*>(m_pMouse)->SetAbleFrameSetTake(true);
	}

	// 스나이퍼 스코프 모드
	if (KEY_DOWN('S'))
	{
		if (m_bIsGetSniper &&
			CAStar::GetInstance()->GetBestList()->empty())
		{
			m_pMouse->SetObjKey(L"SNIPING");
			m_pMouse->SetStateKey(L"Sniping");
			dynamic_cast<CMouse*>(m_pMouse)->SetAbleFrameSetSniping(true);

			m_fSpeed = 0.f;
		}
	}

}

void CPlayer::WorldMatrix()
{
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;
}

void CPlayer::AStarMove()
{
	if (m_bSit)
	{
		return;
	}

	list<int>*	pBestList = CAStar::GetInstance()->GetBestList();
	
	if (pBestList->empty())
	{
		return;
	}

	const vector<TILE*>*	pVecTile = CObjMgr::GetInstance()->GetTile();

	if (nullptr == pVecTile)
	{
		return;
	}

	list<MOVEDIR>*	pMoveDir = CAStar::GetInstance()->GetDirctionList();

	if (nullptr == pMoveDir)
	{
		return;
	}

	int	iMoveIndex = pBestList->front();

	m_tInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - m_tInfo.vPos;
	
	float fDistance = D3DXVec3Length(&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	
	float fTempAngle = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float fRadian = acosf(fTempAngle);

	if (m_tInfo.vPos.y < GetMouse().y - m_vScroll.y)
	{
		fRadian = fOffset * D3DX_PI - fRadian;
	}

	m_fAngle = D3DXToDegree(fRadian);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * GET_TIME;

	if (fDistance < fMaxDis)
	{
		pBestList->pop_front();

		pMoveDir->pop_front();
	}
}

void CPlayer::DrawRect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
	m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
	m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);
}
