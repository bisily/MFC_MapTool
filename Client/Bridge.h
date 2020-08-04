#pragma once

#include "Obj.h"

class CBridge
{
public:
	CBridge();
	CBridge(CObj* pObj);
	virtual ~CBridge();

public:
	virtual HRESULT		Initialize()			PURE;
	virtual int			Progress(INFO& rInfo)	PURE;
	virtual void		Render(HDC hDC)			PURE;
	virtual void		Release()				PURE;

	void	SetFrame(wstring& wstrStateKey);

protected:
	CObj*			m_pObj = nullptr;

	wstring			m_wstrStateKey = L"";
	FRAME			m_tFrame;

};

