#include "stdafx.h"
#include "Enemy.h"
#include "Effect.h"
#include "BridgeFactory.h"
#include "EffectFire.h"
#include "EffectShoot.h"
#include "EffectSplash.h"
#include "EffectDead.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
	Release();
}

HRESULT CEnemy::Initialize()
{
	CString szBuffer = m_wstrStateKey.c_str();

	fCX = 25.f;
	fCY = 42.f;

	m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
	m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
	m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);

	m_iHp = 1;

	m_fSpeed = 30.f;

	int retval = 0;
	retval = szBuffer.Find('_');
	m_wstrStateKey = szBuffer.Left(retval);

	transform(m_wstrStateKey.begin(), m_wstrStateKey.end(), m_wstrStateKey.begin(), towupper);
	m_wstrStateKey = szBuffer.Left(retval);

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_vTempLook = { 1.f, 0.f };

	D3DXVec2Normalize(&m_vTempLook, &m_vTempLook);

	m_tFrame = FRAME(0.f, 3.f, 3.f);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	
	// 위
	if (!lstrcmp(m_wstrStateKey.c_str(), L"DIdleU"))
	{
		m_fAngle = 90.f;
	}

	// 오른쪽 위
	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleRU"))
	{
		m_fAngle = 45.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleR"))
	{
		m_fAngle = 0.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleRB"))
	{
		m_fAngle = 315.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleB"))
	{
		m_fAngle = 270.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleLB"))
	{
		m_fAngle = 225.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleL"))
	{
		m_fAngle = 180.f;
	}

	else if (!lstrcmp(m_wstrStateKey.c_str(), L"EIdleLU"))
	{
		m_fAngle = 135.f;
	}

	m_eLayer = RENDER_OBJ;

	return S_OK;
}

int CEnemy::Progress()
{	
	// 이동 좌표값이 있을 경우 StateKey값을 Walk로 바꿔줌
	if (!m_vRotate.empty() &&
		STATE_ATTECT != m_eStete)
	{
		m_bWork = TRUE;
		m_eStete = STATE_WALK;
		m_ePreSate = STATE_WALK;
	}

	if (m_bWork &&
		0 == m_iTempCnt)
	{
		m_iTempCnt++;
		m_tFrame = { 0.f, 7.f, 7.f };
	}

	vTargetPos = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

	float fDist = D3DXVec3Length(&vTargetPos);

	if (fTarget_len > fDist)
	{
		D3DXVec3Normalize(&vTargetPos, &vTargetPos);

		float	fCos = D3DXVec3Dot(&vTargetPos, &m_tInfo.vLook);
		float	fRadian = acosf(fCos);

		if (m_tInfo.vPos.y < m_pTarget->GetInfo()->vPos.y)
		{
			fRadian = fOffset * D3DX_PI - fRadian;
		}

		m_fTargetAngle = D3DXToDegree(fRadian);
	

		if (abs(m_fAngle - m_fTargetAngle) < fViewAngle)
		{
			m_eStete = STATE_ATTECT;
		}
	}

	// 벡터의 거리가 101 이상이 되고 공격 상태일 경우
	if (101 < fDist &&
		STATE_ATTECT == m_eStete)
	{
		// 이전 상태로 바꿔주고
		m_eStete = m_ePreSate;

		// 이전 상태가 Idle이면 해당 각도의 State키값으로 변경
		if (STATE_IDLE == m_ePreSate)
		{

			if ((0 <= m_fAngle && 18 >= m_fAngle) ||
				(340 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"EIdleR";
			}

			else if (19 <= m_fAngle && 64 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleRU";
			}

			else if (65 <= m_fAngle && 109 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleU";
			}

			else if (110 <= m_fAngle && 155 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleLU";
			}

			else if (156 <= m_fAngle && 201 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleL";
			}

			else if (202 <= m_fAngle && 247 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleLB";
			}

			else if (248 <= m_fAngle && 293 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleB";
			}

			else if (294 <= m_fAngle && 339 >= m_fAngle)
			{
				m_wstrStateKey = L"EIdleRB";
			}

			if (3 != m_tFrame.fMax)
			{
				m_tFrame = FRAME{ 0.f, 3.f, 3.f };
			}
		}

		else if (STATE_WALK == m_ePreSate &&
			7 != m_tFrame.fMax)
		{

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

			if ((0 <= m_fAngle && 22.5 >= m_fAngle) ||
				(337.6 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"EWalkR";
			}

			if (22.6 <= m_fAngle && 67.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkRU";
			}

			if (67.5 <= m_fAngle && 112 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkU";
			}

			if (112.5 <= m_fAngle && 157.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkLU";
			}

			if (157.6 <= m_fAngle && 202.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkL";
			}

			if (202.6 <= m_fAngle && 247.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkLB";
			}

			if (247.6 <= m_fAngle && 292.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkB";
			}

			if (292.6 <= m_fAngle && 337.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkRB";
			}

			if (7 != m_tFrame.fMax)
			{
				m_tFrame = { 0.f, 7.f, 7.f };
			}
		}
	}

	if (STATE_ATTECT == m_eStete)
	{
		AttackPlayer();
	}

	DrawRect();
	FrameMove();

	if (STATE_ATTECT != m_eStete)
	{
		MovePatrol();
	}

	WorldMatrix();

	// 죽었을 경우
	if (m_bDead && 1 >= m_iCnt)
	{
		pEffect = CBridgeFactory<CEffectDead>::CreateEffect(L"DeadEffect", m_tInfo.vPos);
		CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

		if (m_tFrame.fFrame > m_tFrame.fMax)
		{
			return 1;
		}
	}

	return 0;
}

void CEnemy::Render(HDC hDC)
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

void CEnemy::Release()
{
}

void CEnemy::FrameMove()
{
	// 죽지 않았을 경우
	if (!m_bDead && 1 >= m_iHp)
	{
		if (m_bWork &&
			STATE_WALK == m_eStete)
		{
			m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

			if ((0 <= m_fAngle && 22.5 >= m_fAngle) ||
				(337.6 <= m_fAngle && 360 >= m_fAngle))
			{
				m_wstrStateKey = L"EWalkR";
			}

			if (22.6 <= m_fAngle && 67.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkRU";
			}

			if (67.5 <= m_fAngle && 112 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkU";
			}

			if (112.5 <= m_fAngle && 157.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkLU";
			}

			if (157.6 <= m_fAngle && 202.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkL";
			}

			if (202.6 <= m_fAngle && 247.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkLB";
			}

			if (247.6 <= m_fAngle && 292.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkB";
			}

			if (292.6 <= m_fAngle && 337.5 >= m_fAngle)
			{
				m_wstrStateKey = L"EWalkRB";
			}
		}

		if (STATE_IDLE == m_eStete)
		{
			m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;
		}

		if (STATE_IDLE == m_eStete ||
			STATE_WALK == m_eStete)
		{
			if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_tFrame.fFrame = 0.f;
			}
		}

		else if (STATE_ATTECT == m_eStete)
		{
			if (0.f == (int)m_tFrame.fFrame)
			{
				srand((unsigned int)time(NULL));

				if (!m_bFineTarget)
				{
					m_bFineTarget = !m_bFineTarget;

					int iRandom = rand() % 2;

					if (iRandom % 2 == 0)
					{
						CSoundMgr::GetInstance()->PlayerSound(L"Find.wav", CSoundMgr::CHANNEL_ENEMY);
					}
					else
					{
						CSoundMgr::GetInstance()->PlayerSound(L"Find_2.wav", CSoundMgr::CHANNEL_ENEMY);
					}
				}

				D3DXVec3Normalize(&vTargetPos, &vTargetPos);

				float	fCos = D3DXVec3Dot(&vTargetPos, &m_tInfo.vLook);
				float	fRadian = acosf(fCos);

				if (m_tInfo.vPos.y < m_pTarget->GetInfo()->vPos.y)
				{
					fRadian = 2 * D3DX_PI - fRadian;
				}

				m_fTargetAngle = D3DXToDegree(fRadian);

				CString vTempName;
				D3DXVECTOR3 vTempPos;

				if ((0 <= m_fTargetAngle && 22.5 >= m_fTargetAngle) ||
					(337.6 <= m_fTargetAngle && 360 >= m_fTargetAngle))
				{
					vTempName = L"FireR";
					vTempPos = { m_tInfo.vPos.x + 17, m_tInfo.vPos.y - 10, 0.f };
				}

				else if (22.6 <= m_fTargetAngle && 67.5 >= m_fTargetAngle)
				{
					vTempName = L"FireRU";
					vTempPos = { m_tInfo.vPos.x + 14, m_tInfo.vPos.y - 26 / 2, 0.f };
				}

				else if (67.5 <= m_fTargetAngle && 112 >= m_fTargetAngle)
				{
					vTempName = L"FireU";
					vTempPos = { m_tInfo.vPos.x, m_tInfo.vPos.y - 28, 0.f };
				}

				else if (112.5 <= m_fTargetAngle && 157.5 >= m_fTargetAngle)
				{
					vTempName = L"FireLU";
					vTempPos = { m_tInfo.vPos.x - 14, m_tInfo.vPos.y - 28, 0.f };
				}

				else if (157.6 <= m_fTargetAngle && 202.5 >= m_fTargetAngle)
				{
					vTempName = L"FireL";
					vTempPos = { m_tInfo.vPos.x - 17, m_tInfo.vPos.y - 10, 0.f };
				}

				else if (202.6 <= m_fTargetAngle && 247.5 >= m_fTargetAngle)
				{
					vTempName = L"FireLB";
					vTempPos = { m_tInfo.vPos.x - 15, m_tInfo.vPos.y + 22, 0.f };
				}

				else if (247.6 <= m_fTargetAngle && 292.5 >= m_fTargetAngle)
				{
					vTempName = L"FireB";
					vTempPos = { m_tInfo.vPos.x, m_tInfo.vPos.y + 24, 0.f };
				}

				else if (292.6 <= m_fTargetAngle && 337.5 >= m_fTargetAngle)
				{
					vTempName = L"FireRB";
					vTempPos = { m_tInfo.vPos.x + 15, m_tInfo.vPos.y - 5, 0.f };
				}
				
				if (!m_bCoolTime)
				{
					m_bCoolTime = !m_bCoolTime;

					pEffect = CBridgeFactory<CEffectFire>::CreateEffect(vTempName.operator LPCWSTR(), vTempPos);
					CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

					int iVal = rand() % 2;

					float fX = (float)(rand() % 12);

					vTempPos = m_pTarget->GetInfo()->vPos;

					if (iVal == 0)
					{
						vTempPos.x += fX;
					}
					else
					{
						vTempPos.x -= fX;
					}

					// 플레이어 근처에
					pEffect = CBridgeFactory<CEffectShoot>::CreateEffect(L"Shoot", vTempPos);
					CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

					vTempPos = m_pTarget->GetInfo()->vPos;
					
					vTempPos.y += m_pTarget->GetCY() / 2;
				
					iVal = rand() % 2;
					fX = (float)(rand() % 30);
					
					if (iVal == 0)
					{
						vTempPos.x += fX;
					}
					else
					{
						vTempPos.x -= fX;
					}

					// 플레이어 바닥 근처에
					pEffect = CBridgeFactory<CEffectSplash>::CreateEffect(L"Splash", vTempPos);
					CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

					CSoundMgr::GetInstance()->PlayerSound(L"Fire.wav", CSoundMgr::CHANNEL_EFFECT);
				}
			}

			m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

			if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_tFrame.fFrame = 0.f;

				m_bCoolTime = !m_bCoolTime;
			}
		}

		
		// 죽었을 경우의 스프라이트
		if (!m_bDead && 0 >= m_iHp && 0 == m_iCnt)
		{
			m_iCnt++;
			m_bDead = !m_bDead;
			m_fSpeed = 0.f;
			m_wstrStateKey = L"EDead";

			m_tFrame = FRAME(0.f, 4.f, 4.f);
		}
	}

	// 죽었을 경우의 스프라이트
	else if (m_bDead && 0 >= m_iHp)
	{
		if (0 == (int)m_tFrame.fFrame)
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNEL_ENEMY);

			CSoundMgr::GetInstance()->PlayerSound(L"Die.wav", CSoundMgr::CHANNEL_ENEMY);
		}

		if ((int)m_tFrame.fFrame < (int)m_tFrame.fMax)
		{
			m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;
		}
	}
}

void CEnemy::WorldMatrix()
{
	// 움직일 좌표값이 비어 있을 경우
	if (m_vRotate.empty() &&
		STATE_IDLE == m_eStete)
	{
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f);

		m_tInfo.matWorld = matScale * matTrans;
	}

	// 움직일 좌표가 들어 있을 경우
	else if(0 < m_fDist &&
		STATE_WALK == m_eStete)
	{
		m_tInfo.vPos.x += m_vDest.x * m_fSpeed * GET_TIME;
		m_tInfo.vPos.y += m_vDest.y * m_fSpeed * GET_TIME;

		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f);

		m_tInfo.matWorld = matScale * matTrans;
	}

	else if (STATE_ATTECT == m_eStete)
	{
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f);

		m_tInfo.matWorld = matScale * matTrans;
	}
}

void CEnemy::DrawRect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
	m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
	m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);
}

void CEnemy::MovePatrol()
{
	if (!m_vRotate.empty() &&
		STATE_ATTECT != m_eStete)
	{
		// 마지막 요소의 좌표값
		m_vRastDest = m_vRotate.back();

		if (m_iMaxIndex >= m_iIndex)
		{
			// 자신의 좌표를 vector3에서 vector2로 변환
			m_vDest = D3DXVECTOR2(m_tInfo.vPos.x, m_tInfo.vPos.y);

			// 목적지 = 이동 좌표 - 자신의 좌표
			list<D3DXVECTOR2>::iterator vTempDest = m_vRotate.begin();

			for (int i = 0; i < m_iIndex; ++i)
			{
				vTempDest++;
			}

			m_vCurCheckDest = *vTempDest;

			// 방향벡터 생성
			m_vDest.x = vTempDest->x - m_vDest.x;
			m_vDest.y = vTempDest->y - m_vDest.y;

			// 방향벡터의 길이를 구함
			m_fDist = D3DXVec2Length(&m_vDest);

			// 단위 벡터로 바꿈
			D3DXVec2Normalize(&m_vDest, &m_vDest);

			float fTempAngle =	D3DXVec2Dot(&m_vDest, &m_vTempLook);

			float fRadian = acosf(fTempAngle);

			if (m_tInfo.vPos.y < vTempDest->y)
			{
				fRadian = 2 * D3DX_PI - fRadian;
			}

			m_fAngle = D3DXToDegree(fRadian);
			
		}

		if (0 >= (int)m_fDist &&
			m_vCurCheckDest != m_vRastDest)
		{
			++m_iIndex;
		}
		else if (0 >= (int)m_fDist &&
			m_vCurCheckDest == m_vRastDest)
		{
			m_vRotate.reverse();
			m_iIndex = 0;
		}


	}
}

void CEnemy::AttackPlayer()
{
	if (0 >= m_iHp)
	{
		return;
	}

	if (STATE_ATTECT == m_eStete)
	{
		if ((0 <= m_fTargetAngle && 18 >= m_fTargetAngle) ||
			(340 <= m_fTargetAngle && 360 >= m_fTargetAngle))
		{
			m_wstrStateKey = L"EAttackR";
		}

		else if (19 <= m_fTargetAngle && 64 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackRU";
		}

		else if (65 <= m_fTargetAngle && 109 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackU";
		}

		else if (110 <= m_fTargetAngle && 155 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackLU";
		}

		else if (156 <= m_fTargetAngle && 201 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackL";
		}

		else if (202 <= m_fTargetAngle && 247 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackLB";
		}

		else if (248 <= m_fTargetAngle && 293 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackB";
		}

		else if (294 <= m_fTargetAngle && 339 >= m_fTargetAngle)
		{
			m_wstrStateKey = L"EAttackRB";
		}

		if (STATE_ATTECT == m_eStete &&
			3 != m_tFrame.fMax)
		{
			m_tFrame = FRAME{ 0.f, 3.f, 3.f };
		}
	}
}
