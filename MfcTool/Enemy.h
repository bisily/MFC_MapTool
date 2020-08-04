#pragma once
#include "Obj.h"
#include "MainFrm.h"
#include "MfcToolView.h"

class CEnemy :
	public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	CMfcToolView*		m_MainView;
};