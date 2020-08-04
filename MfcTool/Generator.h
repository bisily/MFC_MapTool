#pragma once
#include "Obj.h"
class CGenerator :
	public CObj
{
public:
	CGenerator();
	virtual ~CGenerator();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CMfcToolView*		m_MainView;
};

