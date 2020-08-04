#pragma once
#include "Obj.h"
class CSniperRifle :
	public CObj
{
public:
	CSniperRifle();
	virtual ~CSniperRifle();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void DrawRect();
};

