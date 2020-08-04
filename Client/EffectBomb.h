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
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

