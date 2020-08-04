#pragma once
#include "Obj.h"
class CDrum :
	public CObj
{
public:
	CDrum();
	virtual ~CDrum();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CMfcToolView*		m_MainView;
};

