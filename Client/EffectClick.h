#pragma once

#include "EffectBridge.h"

class CEffectClick :
	public CEffectBridge
{
public:
	CEffectClick();
	CEffectClick(CObj* pObj);
	virtual ~CEffectClick();

public:
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

