#pragma once
#include "Obj.h"

class CEnemy :
	public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	SetTaret(CObj* pTarget) { m_pTarget = pTarget; }
	//void	SetAttak() { m_bAttack = true; }
	//void	SetOffAttak() { m_bAttack = false; }
	void	SetRotate(D3DXVECTOR2 vRotate) { m_vRotate.push_back(vRotate); }
	void	SetMaxRotateSize() { m_iMaxIndex = m_vRotate.size(); }

private:
	void	FrameMove();
	void	WorldMatrix();
	void	DrawRect();

	void	MovePatrol();
	void	AttackPlayer();

private:
	STATEID				m_eStete = STATE_IDLE;
	STATEID				m_ePreSate = STATE_IDLE;
	
	bool				m_bDead = false;
	bool				m_bWork = false;
	bool				m_bCoolTime = false;
	bool				m_bFineTarget = false;

	int					m_iTempCnt = 0;
	int					m_iCnt = 0;
	int					m_iIndex = 0;
	int					m_iMaxIndex = 0;
	float				m_fDist = 0.f;
	float				m_fAngle;
	float				m_fTargetAngle;

	CObj*				m_pTarget = nullptr;
	CObj*				pEffect = nullptr;
	list<D3DXVECTOR2>	m_vRotate;
	D3DXVECTOR2			m_vDest, m_vRastDest, m_vCurCheckDest, m_vTempLook;
	D3DXVECTOR3			vTargetPos;
	D3DXMATRIX			matScale, matTrans;
	float				fOffset = 2.0f;
	float				fTarget_len = 100.f;
	float				fViewAngle = 30.f;
};