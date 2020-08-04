#pragma once

#include "EffectBridge.h"

class CEffectBomb :
	public CEffectBridge

{
public:
	CEffectBomb();
	CEffectBomb(CObj* pObj);
	virtual ~CEffectBomb();

public:
	// CEffectBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

