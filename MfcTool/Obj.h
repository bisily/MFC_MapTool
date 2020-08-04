#pragma once

#include "Include.h"

class CObj
{
protected:
	INFO		m_tInfo{};
	FRAME		m_tFrame{};
	DATA		m_tData{};

	float		m_fSpeed = 0.f;
	wstring		m_wstrObjKey = L"";
	wstring		m_wstrStateKey = L"";
	wstring		m_wstrCount = L"";
	
	static		D3DXVECTOR3		m_vScroll;

	list<D3DXVECTOR2>		m_vRotate;
	int						m_iIndex;

public:
	const INFO*			GetInfo(void) const { return &m_tInfo; }
	const float			GetSpeed() const { return m_fSpeed; }
	const wstring&		GetObjKey() { return m_wstrObjKey; }
	const wstring&		GetStateKey() { return m_wstrStateKey; }
	const wstring&		GetCount() { return m_wstrCount; }
	list<D3DXVECTOR2>&	GetRoateList() { return m_vRotate; }
	const int			GetIndex() { return m_iIndex; }

public:
	void				SetIndex(int iIndex) { m_iIndex = iIndex; }
	void				SetPos(const D3DXVECTOR3& vPos) { m_tInfo.vPos = vPos; }
	void				SetRotate(D3DXVECTOR2 vRotate) { m_vRotate.push_back(vRotate); }
	void				SetPos(float _fX, float _fY)
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
		m_tInfo.vPos.z = 0.f;
	}

	void				SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void				SetObjKey(const wstring& FileName) { m_wstrObjKey = FileName; }
	void				SetStateKey(const wstring& StateKey) { m_wstrStateKey = StateKey; }
	
public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Progress(void)	PURE;
	virtual void		Render(void)	PURE;
	virtual void		Release(void)	PURE;

public:
	CObj();
	virtual ~CObj();
};

