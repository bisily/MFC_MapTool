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
	virtual void Render() override;
	virtual void Release() override;

private:
	CMfcToolView*		m_MainView;
};

