#pragma once
#include "Obj.h"
class CSniperRifle :
	public CObj
{
public:
	CSniperRifle();
	virtual ~CSniperRifle();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void DrawRect();
};

