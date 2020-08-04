#pragma once
#include "Obj.h"
class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

