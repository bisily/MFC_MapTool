#pragma once
#include "Obj.h"
#include "MainFrm.h"
#include "MfcToolView.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	CMfcToolView*		m_MainView;
};

