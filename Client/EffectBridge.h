#pragma once
#include "Bridge.h"
class CEffectBridge :
	public CBridge
{
public:
	CEffectBridge();
	CEffectBridge(CObj* pObj);
	virtual ~CEffectBridge();

public:
	// CBridge을(를) 통해 상속됨
	virtual HRESULT		Initialize() PURE;
	virtual int			Progress(INFO & rInfo) PURE;
	virtual void		Render(HDC hDC);
	virtual void		Release() PURE;

};

