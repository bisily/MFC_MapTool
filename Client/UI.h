#pragma once
#include "Obj.h"
class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

