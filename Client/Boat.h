#pragma once
#include "Obj.h"
class CBoat :
	public CObj
{
public:
	CBoat();
	virtual ~CBoat();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetTarget(CObj* pObj) { m_pTarget = pObj; }

private:
	void DrawRect();
	void KeyCheck();

private:
	D3DXMATRIX			matScale, matTrans;
	CObj*				m_pTarget = nullptr;

};

