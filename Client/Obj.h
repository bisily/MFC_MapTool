#pragma once

#include "Include.h"

class CBridge;
class CObj
{
protected:
	INFO		m_tInfo{};
	FRAME		m_tFrame{};
	CBridge*	m_pBridge = nullptr;
	RECT		m_tRect{};

	float		fCX = 0;
	float		fCY = 0;

	float		m_fSpeed = 0.f;
	wstring		m_wstrObjKey = L"";
	wstring		m_wstrStateKey = L"";
	wstring		m_wstrCount = L"";

	int			m_iHp = 0;

	RENDERID	m_eLayer;

	static		D3DXVECTOR3		m_vScroll;

public:
	const INFO*		GetInfo() const { return &m_tInfo; }
	const float		GetSpeed() const { return m_fSpeed; }
	const wstring&	GetObjKey() { return m_wstrObjKey; }
	const wstring&	GetStateKey() { return m_wstrStateKey; }
	const wstring&	GetCount() { return m_wstrCount; }
	CBridge*		GetBridge() const { return m_pBridge; }
	RENDERID		GetLayer() { return m_eLayer; }
	const RECT		GetRect() { return m_tRect; }
	const int 		GetHP() { return m_iHp; }
	const float		GetCX() { return fCX; }
	const float		GetCY() { return fCY; }
	const D3DXVECTOR3 GetScroll() { return m_vScroll; }

public:
	void		SetHP(int Hp) { m_iHp += Hp; }
	void		SetBridge(CBridge* pBridge) { m_pBridge = pBridge; }
	void		SetPos(const D3DXVECTOR3& vPos) { m_tInfo.vPos = vPos; }
	void		SetPos(float _fX, float _fY)
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
		m_tInfo.vPos.z = 0.f;
	}
	void		SetCX(float _fCX) { fCX = _fCX; }
	void		SetCY(float _fCY) { fCY = _fCY; }
	void		SetRect() 
	{
		m_tRect.left = LONG(m_tInfo.vPos.x - fCX / 2);
		m_tRect.top = LONG(m_tInfo.vPos.y - fCY / 2);
		m_tRect.right = LONG(m_tInfo.vPos.x + fCX / 2);
		m_tRect.bottom = LONG(m_tInfo.vPos.y + fCY / 2);
	}

	void		SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void		SetObjKey(const wstring& FileName) { m_wstrObjKey = FileName; }
	void		SetStateKey(const wstring& StateKey) { m_wstrStateKey = StateKey; }

public:
	virtual HRESULT		Initialize()	PURE;
	virtual int			Progress()		PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

public:
	CObj();
	virtual ~CObj();
};

