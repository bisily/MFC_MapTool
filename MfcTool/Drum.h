#pragma once
#include "Obj.h"
class CDrum :
	public CObj
{
public:
	CDrum();
	virtual ~CDrum();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CMfcToolView*		m_MainView;
};

