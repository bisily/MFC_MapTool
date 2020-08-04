#pragma once
#include "Obj.h"

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
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void DrawRect();

};

