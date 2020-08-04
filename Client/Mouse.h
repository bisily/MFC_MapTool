#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	SetAbleFrameSetHand(bool CheckFrame) { m_bCheckFrame = CheckFrame; }
	void	SetAbleFrameSetTake(bool CheckFrame) { m_bCheckTake = CheckFrame; }
	void	SetAbleFrameSetSniping(bool CheckFrame) { m_bCheckSniping = CheckFrame; }

private:
	void	FrameMove();
	void	WorldMatrix();

private:
	bool	m_bCheckFrame = false;
	bool	m_bCheckTake = false;
	bool	m_bCheckSniping = false;
};

