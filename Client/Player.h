#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	SetFrame(FRAME _tFrame) { m_tFrame = _tFrame; }
	void	SetMouse(CObj* pMouse) { m_pMouse = pMouse; }
	void	SetKnifeAttact() { m_bKnifeAttack = true; }
	void	SetDrum(CObj* pDrum) { m_pDrum = pDrum; }
	void	SetSit() { m_bSit = true; }
	void	SetStand() { m_bSit = false; }
	void	SetGetSniper() { m_bIsGetSniper = true; }

private:
	void	CheckKey();
	void	FrameMove();
	void	WorldMatrix();
	void	AStarMove();
	void	DrawRect();

private:
	bool			m_bPressingButton = false;
	bool			m_bKnifeAttack = false;
	bool			m_bFireSound = false;
	bool			m_bWalkSound = false;
	bool			m_bSit = false;
	bool			m_bIsGetSniper = false;

	float			m_fAngle = 270.f;
	D3DXVECTOR3		m_vDir;
	D3DXMATRIX		matScale, matTrans;

	CObj*			m_pMouse = nullptr;
	CObj*			m_pDrum = nullptr;
	float			fMaxDis = 5.0f;
	float			fOffset = 2.0f;
};

