#pragma once
#include "Obj.h"
#include "MainFrm.h"
#include "MfcToolView.h"

class CBuilding :
	public CObj
{
public:
	CBuilding();
	virtual ~CBuilding();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	CMfcToolView*		m_MainView;
};

