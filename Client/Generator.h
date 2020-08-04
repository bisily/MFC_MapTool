#pragma once
#include "Obj.h"
class CGenerator :
	public CObj
{
public:
	CGenerator();
	virtual ~CGenerator();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int			m_iCreateCnt = 0;
	double		m_dExplosionTime = 0;
};

