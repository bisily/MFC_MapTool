#pragma once
#include "EffectBridge.h"
class CEffectSplash :
	public CEffectBridge
{
public:
	CEffectSplash();
	CEffectSplash(CObj* pObj);
	virtual ~CEffectSplash();

public:
	// CEffectBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

